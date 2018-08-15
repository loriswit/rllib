#define RL_ASSERT_IN_RANGE(i) \
    RL_ASSERT((i) <= m_data.size(), \
    "reading out of range (" + std::to_string(i) + " > " + std::to_string(m_data.size()) + ')');

template<typename T, EnableIfNumeric<T> *>
T ByteStream::get()
{
    T value;
    RL_ASSERT_IN_RANGE(m_pos + sizeof(T));
    auto ptr = reinterpret_cast<Byte *>(&value);
    std::reverse_copy(m_data.begin() + m_pos, m_data.begin() + m_pos + sizeof(T), ptr);
    m_pos += sizeof(T);
    return value;
}

template<typename T, EnableIfSerializable<T> *>
T ByteStream::get()
{
    T value;
    value.deserialize(*this);
    return value;
}

template<typename T, EnableIfArray<T> *>
T ByteStream::get()
{
    auto size = get<uint32_t>();
    
    T array;
    array.reserve(size);
    for(unsigned i = 0; i < size; ++i)
        array.push_back(get<typename T::value_type>());
    
    return array;
}

template<typename T, EnableIfByteStream<T> *>
T ByteStream::get()
{
    ByteStream data(m_data.size() - m_pos);
    std::copy(m_data.cbegin() + m_pos, m_data.cend(), data.begin());
    m_pos += data.size();
    return data;
}

template<typename T>
T ByteStream::get(std::size_t pos)
{
    seek(pos);
    return get<T>();
}

template<typename T>
ByteStream & ByteStream::operator>>(T & value)
{
    value = get<T>();
    return *this;
}

template<typename T, EnableIfNumeric<T> *>
void ByteStream::put(const T & value)
{
    if(m_pos + sizeof(T) > m_data.size())
        m_data.resize(m_pos + sizeof(value));
    
    auto ptr = reinterpret_cast<const Byte *>(&value);
    std::reverse_copy(ptr, ptr + sizeof(T), m_data.begin() + m_pos);
    m_pos += sizeof(T);
}

template<typename T, EnableIfSerializable<T> *>
void ByteStream::put(const T & value)
{
    put(value.serialize());
}

template<typename T, EnableIfArray<T> *>
void ByteStream::put(const T & value)
{
    put(static_cast<uint32_t>(value.size()));
    for(const auto & item : value)
        put(item);
}

template<typename T>
void ByteStream::put(const T & value, std::size_t pos)
{
    seek(pos);
    put(value);
}

template<typename T>
ByteStream & ByteStream::operator<<(const T & value)
{
    put(value);
    return *this;
}
