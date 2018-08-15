#ifndef RLLIB_FILEWRITER_HPP
#define RLLIB_FILEWRITER_HPP

#include <fstream>

#include <rllib/stream/ByteStream.hpp>
#include <rllib/util/FilePath.hpp>

namespace rl
{

/**
 * The file reader provides features to write bytes into a binary file.
 */
class FileWriter
{
public:
    /**
     * Creates and opens a file with writing permissions.
     * If the file does not exist, it is created.
     * If the file already exists, the original content can be either kept or discarded.
     *
     * @param path The path to the file
     * @param truncate <code>true</code> to discard the original content, <code>false</code> to keep it
     */
    explicit FileWriter(const FilePath & path, bool truncate = false);
    
    /**
     * Opens a file with writing permissions.
     * If the file does not exist, it is created.
     * If the file already exists, the original content can be either kept or discarded.
     *
     * @param path The path to the file
     * @param truncate <code>true</code> to discard the original content, <code>false</code> to keep it
     */
    void open(const FilePath & path, bool truncate = false);
    
    /**
     * Tells if the file is in a good state.
     *
     * @return <code>true</code> if no errors occurred while writing into the file,
     * <code>false</code> if something went wrong
     */
    operator bool() const;
    
    /**
     * Writes a chunk of bytes into the file.
     *
     * @param buffer The data stream containing the bytes that are to be written
     */
    void write(const ByteStream & buffer);
    
    /**
     * Writes a chunk of bytes into a specific position in the file.
     *
     * @param buffer The data stream containing the bytes that are to be written
     * @param pos The position of the file cursor
     */
    void write(const ByteStream & buffer, std::streampos pos);
    
private:
    std::fstream m_file;
    
};

} // namespace rl

#endif //RLLIB_FILEWRITER_HPP
