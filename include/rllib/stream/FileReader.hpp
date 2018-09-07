#ifndef RLLIB_FILEREADER_HPP
#define RLLIB_FILEREADER_HPP

#include <fstream>

#include <rllib/stream/ByteStream.hpp>
#include <rllib/util/FilePath.hpp>

namespace rl
{

/**
 * The file reader provides features to read bytes from a binary file.
 */
class RL_API FileReader
{
public:
    /**
     * Creates and opens a file with reading permissions.
     *
     * @param path The path to the file
     */
    explicit FileReader(const FilePath & path);
    
    /**
     * Opens a file with reading permissions.
     *
     * @param path The path to the file
     */
    void open(const FilePath & path);
    
    /**
     * Tells if the file is in a good state.
     *
     * @return <code>true</code> if no errors occurred while reading the file,
     * <code>false</code> if something went wrong
     */
    operator bool() const;
    
    /**
     * Reads a chunk of bytes from the file.
     *
     * @param size The number of bytes that are to be read
     * @return A data stream containing the bytes
     */
    ByteStream read(std::size_t size);
    
    /**
     * Reads a chunk of bytes from a specific position in the file.
     *
     * @param size The number of bytes that are to be read
     * @param pos The position of the file cursor
     * @return A data stream containing the bytes
     */
    ByteStream read(std::size_t size, std::streampos pos);
    
    /**
     * Reads all bytes from the file.
     *
     * @return A data stream containing all bytes
     */
    ByteStream readAll();
    
private:
    std::ifstream m_file;
};

} // namespace rl

#endif //RLLIB_FILEREADER_HPP
