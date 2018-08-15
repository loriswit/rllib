#include <rllib/stream/FileReader.hpp>

namespace rl
{

FileReader::FileReader(const FilePath & path)
{
    open(path);
}

void FileReader::open(const FilePath & path)
{
    m_file.open(path, std::ios::in | std::ios::binary);
    if(!m_file)
        throw std::runtime_error("could not open file " + path + " for reading");
}

FileReader::operator bool() const
{
    return !m_file.fail();
}

ByteStream FileReader::read(std::size_t size)
{
    ByteStream buffer(size);
    m_file.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
    
    if(!m_file)
        throw std::runtime_error("could not read file");
    return buffer;
}

ByteStream FileReader::read(std::size_t size, std::streampos pos)
{
    m_file.seekg(pos);
    return read(size);
}

ByteStream FileReader::readAll()
{
    m_file.seekg(0, std::ios::end);
    auto size = static_cast<std::size_t>(m_file.tellg());
    return read(size, 0);
}

} // namespace rl
