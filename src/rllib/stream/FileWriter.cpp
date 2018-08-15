#include <rllib/stream/FileWriter.hpp>

namespace rl
{

FileWriter::FileWriter(const FilePath & path, bool truncate)
{
    open(path, truncate);
}

void FileWriter::open(const FilePath & path, bool truncate)
{
    if(!truncate)
        m_file.open(path, std::ios::in | std::ios::out | std::ios::binary);
    if(truncate || !m_file)
        m_file.open(path, std::ios::out | std::ios::binary);
    if(!m_file)
        throw std::runtime_error("could not open file " + path + " for writing");
}

FileWriter::operator bool() const
{
    return !m_file.fail();
}

void FileWriter::write(const ByteStream & buffer)
{
    m_file.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
    
    if(!m_file)
        throw std::runtime_error("could not write into file");
}

void FileWriter::write(const ByteStream & buffer, std::streampos pos)
{
    m_file.seekp(pos);
    return write(buffer);
}

} // namespace rl
