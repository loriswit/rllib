#ifndef RLLIB_BYTESTREAM_HPP
#define RLLIB_BYTESTREAM_HPP

#include <vector>
#include <algorithm>

#include <rllib/util/Byte.hpp>
#include <rllib/util/Error.hpp>

namespace rl
{

class ByteStream;

template<typename T>
using EnableIfNumeric = std::enable_if_t<std::is_arithmetic_v<T>>;

template<typename T>
using EnableIfSerializable = std::enable_if_t<
        std::is_same_v<decltype(std::declval<T>().serialize()), ByteStream> &&
        std::is_same_v<decltype(std::declval<T>().deserialize(std::declval<ByteStream &>())), void>>;

template<typename T>
using EnableIfArray = std::enable_if_t<
        std::is_same_v<decltype(std::declval<T>().begin()), typename T::iterator> &&
        std::is_same_v<decltype(std::declval<T>().end()), typename T::iterator> &&
        std::is_same_v<decltype(std::declval<T>().size()), typename T::size_type> &&
        std::is_same_v<decltype(std::declval<T>().reserve()), void>>;

template<typename T>
using EnableIfByteStream = std::enable_if_t<std::is_same_v<T, ByteStream>>;


/**
 * This class represents a data stream containing a variable number of bytes.
 * It provides features to extract and write values from and into the stream.
 */
class ByteStream
{
public:
    /**
     * Creates an empty data stream
     */
    ByteStream() = default;
    
    /**
     * Creates a data stream containing a specific number of bytes.
     *
     * @param size The initial number of bytes in the data stream
     */
    explicit ByteStream(std::size_t size);
    
    /**
     * Returns the number of bytes in the data stream.
     *
     * @return The number of bytes
     */
    std::size_t size() const noexcept;
    
    /**
     * Sets the number of bytes in the data stream.
     *
     * @param size The number of bytes
     */
    void resize(std::size_t size);
    
    /**
     * Returns a raw pointer to the first byte.
     *
     * @return The pointer to the first byte
     */
    Byte * data() noexcept;
    
    /**
     * Returns a raw pointer to the first byte (const).
     *
     * @return The pointer to the first byte (const)
     */
    const Byte * data() const noexcept;
    
    /**
     * @return An iterator pointing to the first byte
     */
    std::vector<Byte>::iterator begin() noexcept;
    
    /**
     * @return An iterator pointing to the first byte (const)
     */
    std::vector<Byte>::const_iterator cbegin() const noexcept;
    
    /**
     * @return An iterator pointing to the last byte
     */
    std::vector<Byte>::iterator end() noexcept;
    
    /**
     * @return An iterator pointing to the last byte (const)
     */
    std::vector<Byte>::const_iterator cend() const noexcept;
    
    /**
     * Returns the position of the stream cursor.
     *
     * @return The stream position
     */
    std::size_t tell() const noexcept;
    
    /**
     * Sets the position of the stream cursor.
     *
     * @param pos The new stream position
     */
    void seek(std::size_t pos) noexcept;
    
    /**
     * Reads an numeric value from the stream.
     * If the data to read is out of bound, the behavior is undefined.
     *
     * @tparam T The type of the numeric value
     * @return The value extracted from the stream
     */
    template<typename T, EnableIfNumeric<T> * = nullptr>
    T get();
    
    /**
     * Extracts an serializable object from the stream.
     * If the data to read is out of bound, the behavior is undefined.
     *
     * @tparam T The type of the serializable object
     * @return The object deserialized from the stream
     */
    template<typename T, EnableIfSerializable<T> * = nullptr>
    T get();
    
    /**
     * Reads an array from the stream.
     * If the data to read is out of bound, the behavior is undefined.
     *
     * @tparam T The type of the array
     * @return The array extracted from the stream
     */
    template<typename T, EnableIfArray<T> * = nullptr>
    T get();
    
    /**
     * Reads raw data from the stream.
     * If the data to read is out of bound, the behavior is undefined.
     *
     * @tparam T The type of the raw data
     * @return The data extracted from the stream
     */
    template<typename T, EnableIfByteStream<T> * = nullptr>
    T get();
    
    /**
     * Reads a value from a specific position in the stream.
     * If the data to read is out of bound, the behavior is undefined.
     *
     * @tparam T The type of the value that is to be read
     * @param pos The position of the stream cursor
     * @return The value extracted from the stream
     */
    template<typename T>
    T get(std::size_t pos);
    
    /**
     * Reads a value from the stream and stores it into a variable.
     * If the data to read is out of bound, the behavior is undefined.
     *
     * @tparam T The type of the value that is to be read
     * @param value A reference to the variable where the result will be stored
     * @return The current data stream
     */
    template<typename T>
    ByteStream & operator>>(T & value);
    
    /**
     * Writes an arithmetic value into the stream.
     *
     * @param value The value that is to be written
     */
    template<typename T, EnableIfNumeric<T> * = nullptr>
    void put(const T & value);
    
    /**
     * Serializes an object into the stream.
     *
     * @param value The serializable object that is to be written
     */
    template<typename T, EnableIfSerializable<T> * = nullptr>
    void put(const T & value);
    
    /**
     * Writes a array into the stream.
     *
     * @param value The array that is to be written
     */
    template<typename T, EnableIfArray<T> * = nullptr>
    void put(const T & value);
    
    /**
     * Writes a string into the stream.
     *
     * @param value The string that is to be written
     */
    void put(const char * value);
    
    /**
     * Writes raw data into the stream.
     *
     * @param value A byte stream containing the data
     */
    void put(const ByteStream & value);
    
    /**
     * Writes a value into a specific position in the stream.
     *
     * @tparam T The type of the value that is to be written
     * @param value The value that is to be written
     * @param pos The position of the stream cursor
     */
    template<typename T>
    void put(const T & value, std::size_t pos);
    
    /**
     * Writes a value into the stream.
     *
     * @tparam T
     * @param value
     * @return
     */
    template<typename T>
    ByteStream & operator<<(const T & value);

private:
    std::vector<Byte> m_data;
    
    std::size_t m_pos = 0;
};

#include "ByteStream.inl"

} // namespace rl

#endif //RLLIB_BYTESTREAM_HPP
