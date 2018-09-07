#ifndef RLLIB_FILEPATH_HPP
#define RLLIB_FILEPATH_HPP

#include <rllib/stream/Serializable.hpp>

namespace rl
{

/**
 * Structure containing a normalized file path.
 */
struct RL_API FilePath
{
    /**
     * The directory of the file.
     */
    std::string directory;
    
    /**
     * The name of the file.
     */
    std::string filename;
    
    /**
     * Creates an empty file path.
     */
    FilePath() = default;
    
    /**
     * Creates a file path.
     *
     * @param dir The directory of the file
     * @param name The name of the file
     */
    FilePath(const std::string & dir, const std::string & name);
    
    /**
     * Creates a file path.
     *
     * @param path The full path of the file
     */
    FilePath(const std::string & path);
    
    /**
     * Creates a file path.
     *
     * @param path The full path of the file
     */
    FilePath(const char * path);
    
    /**
     * Converts the file path into a string.
     *
     * @return A string containing the directory and the filename
     */
    operator std::string() const;
    
    /**
     * Compares the file path with another one.
     *
     * @param other The other file path
     * @return <code>true</code> if both paths are the same, <code>false</code> if not
     */
    bool operator==(const FilePath & other) const noexcept;
    
    SERIALIZE(directory, filename)
};

/**
 * Appends a file path to the end of a string.
 *
 * @param str The string object
 * @param path The file path
 * @return A string containing the result
 */
std::string operator+(const std::string & str, const FilePath & path);

/**
 * Writes a file path into a stream.
 *
 * @param stream The stream object
 * @param path The file path
 * @return The current stream
 */
std::ostream & operator<<(std::ostream & stream, const FilePath & path);

} // namespace rl

#endif //RLLIB_FILEPATH_HPP
