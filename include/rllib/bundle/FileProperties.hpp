#ifndef RLLIB_FILEINFO_HPP
#define RLLIB_FILEINFO_HPP

#include <rllib/util/FilePath.hpp>
#include <rllib/stream/Serializable.hpp>

namespace rl
{

/**
 * This structure holds properties about a file in the bundle.
 */
struct FileProperties
{
    /**
     * An unknown value at the start of the structure.
     */
    uint32_t header = 1;
    
    /**
     * The size of the file content.
     */
    uint32_t size = 0;
    
    /**
     * The size of the file content once compressed.
     * If this value is null, then the file is not compressed.
     */
    uint32_t cmpSize = 0;
    
    /**
     * The time when the file has been modified.
     */
    int64_t time = 0;
    
    /**
     * The offset of the file content in the bundle.
     */
    uint64_t offset = 0;
    
    /**
     * The file path in the bundle.
     */
    FilePath path;
    
    /**
     * An unknown value, maybe the file checksum.
     */
    uint32_t checksum = 0;
    
    /**
     * An unknown value at the end of the structure.
     */
    uint32_t footer = 0;
    
    /**
     * Creates a file properties structure.
     */
    FileProperties();
    
    /**
     * Sets the time when the file has been modified to now.
     */
    void touch();
    
    SERIALIZE(header, size, cmpSize, time, offset, path, checksum, footer)
};

} // namespace rl

#endif //RLLIB_FILEINFO_HPP
