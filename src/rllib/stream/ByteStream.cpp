#include <rllib/stream/ByteStream.hpp>

namespace rl
{

ByteStream::ByteStream(std::size_t size) : m_data(size)
{
}

std::size_t ByteStream::size() const noexcept
{
    return m_data.size();
}

void ByteStream::resize(std::size_t size)
{
    m_data.resize(size);
}


const Byte * ByteStream::data() const noexcept
{
    return m_data.data();
}

Byte * ByteStream::data() noexcept
{
    return m_data.data();
}

std::vector<Byte>::iterator ByteStream::begin() noexcept
{
    return m_data.begin();
}

std::vector<Byte>::const_iterator ByteStream::cbegin() const noexcept
{
    return m_data.cbegin();
}

std::vector<Byte>::iterator ByteStream::end() noexcept
{
    return m_data.end();
}

std::vector<Byte>::const_iterator ByteStream::cend() const noexcept
{
    return m_data.cend();
}

void ByteStream::seek(std::size_t pos) noexcept
{
    m_pos = pos;
}

std::size_t ByteStream::tell() const noexcept
{
    return m_pos;
}

void ByteStream::put(const char * value)
{
    put(std::string(value));
}

void ByteStream::put(const ByteStream & value)
{
    if(m_pos + value.size() > m_data.size())
        m_data.resize(m_pos + value.size());
    
    std::copy(value.cbegin(), value.cend(), m_data.begin() + m_pos);
    m_pos += value.size();
}

} // namespace rl
