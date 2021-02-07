#include <rllib/bundle/Bundle.hpp>
#include <rllib/stream/FileReader.hpp>
#include <rllib/stream/FileWriter.hpp>

#include "../util/Compress.hpp"

namespace rl
{

Bundle::Bundle(FilePath path)
{
    load(std::move(path));
}

void Bundle::load(FilePath path)
{
    m_path = std::move(path);
    FileReader file(m_path);
    
    auto header = file.read(0x30);
    m_baseOffset = header.get<uint64_t>(0x8);
    auto fileCount = header.get<uint32_t>(0x2c);
    
    auto buffer = file.read(m_baseOffset, 0);
    buffer.seek(0x30);
    
    m_fileList.resize(fileCount);
    for(auto &[fileInfo, offset] : m_fileList)
    {
        offset = buffer.tell();
        buffer >> fileInfo;
    }
}

ByteStream Bundle::readFile(const FilePath & path) const
{
    auto & fileInfo = findFile(path).first;
    
    FileReader file(m_path);
    if(fileInfo.cmpSize)
    {
        auto buffer = file.read(fileInfo.cmpSize, fileInfo.offset + m_baseOffset);
        return inflate(buffer, fileInfo.size);
    }
    else
        return file.read(fileInfo.size, fileInfo.offset + m_baseOffset);
}

void Bundle::writeFile(const FilePath & path, const ByteStream & data)
{
    // assume available space is equal to file size
    auto[fileInfo, offset] = findFile(path);
    auto available = fileInfo.cmpSize ? fileInfo.cmpSize : fileInfo.size;
    auto fileSize = static_cast<uint32_t>(data.size());
    uint32_t cmpSize = 0;
    
    auto buffer = data;
    
    if(fileSize > available)
    {
        // compute real amount of available space
        uint64_t nextAddress = 0;
        for(const auto &[f, o] : m_fileList)
            if(f.offset >= fileInfo.offset + available
               && (!nextAddress || f.offset < nextAddress))
            {
                nextAddress = f.offset;
                if(nextAddress == fileInfo.offset + available)
                    break;
            }
        
        auto totalAvailable = nextAddress - fileInfo.offset;
        if(fileSize > totalAvailable)
        {
            // compress data to save space
            buffer = deflate(buffer);
            cmpSize = static_cast<uint32_t>(buffer.size());
            if(cmpSize > totalAvailable)
                throw std::runtime_error("not enough space available");
        }
    }
    
    auto newFileInfo = fileInfo;
    
    newFileInfo.size = fileSize;
    newFileInfo.cmpSize = cmpSize;
    newFileInfo.touch();
    
    FileWriter file(m_path);
    file.write(newFileInfo, offset);
    file.write(buffer, newFileInfo.offset + m_baseOffset);
}

Bundle Bundle::create(FilePath bundlePath, const std::vector<std::pair<FilePath, ByteStream>> & files)
{
    auto filecount = static_cast<uint32_t>(files.size());
    
    ByteStream buffer;
    buffer << 0x50EC12BA << 5 << 0 << 0 << filecount;
    buffer << 0 << 1 << 1 << 0 << 0x4BFC7C03 << 0 << filecount;
    
    Bundle bundle;
    std::uint64_t nextOffset = 0;
    
    for(const auto &[path, data] : files)
    {
        FileProperties fileInfo;
        fileInfo.path = path;
        fileInfo.size = static_cast<uint32_t>(data.size());
        fileInfo.offset = nextOffset;
        fileInfo.touch();
        
        bundle.m_fileList.emplace_back(fileInfo, buffer.tell());
        buffer << fileInfo;
        nextOffset += fileInfo.size;
    }
    
    bundle.m_path = std::move(bundlePath);
    FileWriter file(bundle.m_path, true);
    
    bundle.m_baseOffset = buffer.size();
    buffer.put<uint64_t>(bundle.m_baseOffset, 0x8);
    file.write(buffer);
    
    for(const auto &[path, data] : files)
        file.write(data);
    
    return bundle;
}

const std::pair<FileProperties, std::streampos> & Bundle::findFile(const FilePath & path) const
{
    auto fileInfo = std::find_if(m_fileList.cbegin(), m_fileList.cend(), [&path](auto & f)
    {
        return f.first.path == path;
    });
    
    if(fileInfo == m_fileList.end())
        throw std::runtime_error("file " + path + " not found in bundle");
    
    return *fileInfo;
}

} // namespace rl
