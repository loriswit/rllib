#ifndef RLLIB_BUNDLE_HPP
#define RLLIB_BUNDLE_HPP

#include <string>

#include <rllib/stream/ByteStream.hpp>
#include <rllib/bundle/FileProperties.hpp>

namespace rl
{

/**
 * A bundle is a collection of files packed in a big single file. It is used to store all the game assets.
 * In particular, this is where scene are being extracted from the game.
 */
class Bundle
{
public:
    /**
     * Creates an empty bundle.
     */
    Bundle() = default;
    
    /**
     * Creates a bundle loaded from a file.
     *
     * @param path The path to the bundle file
     */
    explicit Bundle(FilePath path);
    
    /**
     * Load the bundle from a file.
     *
     * @param path The path to the bundle file
     */
    void load(FilePath path);
    
    /**
     * Reads a file in the bundle and returns its content.
     *
     * @param path The path to the file in the bundle
     * @return The content of the file
     */
    ByteStream readFile(const FilePath & path) const;
    
    /**
     * Overwrites a file in the bundle.
     * The file path must already exist in the bundle.
     *
     * @warning The original content will be lost.
     *
     * @param path The path to the file in the bundle
     * @param data The data that is to be written
     */
    void writeFile(const FilePath & path, const ByteStream & data);
    
    /**
     * Creates a new bundle file and returns its instance.
     *
     * @param bundlePath The path to the new bundle file that is to be created
     * @param files A list of pairs containing file paths with associated contents
     * @return The instance of the new bundle
     */
    static Bundle create(FilePath bundlePath, const std::vector<std::pair<FilePath, ByteStream>> & files);

private:
    /**
     * Finds a file in the bundle index and returns its properties.
     *
     * @param path The path to the file in the bundle
     * @return A pair containing the file properties and the offset of the properties
     */
    const std::pair<FileProperties, std::streampos> & findFile(const FilePath & path) const;
    
    FilePath m_path;
    std::vector<std::pair<FileProperties, std::streampos>> m_fileList;
    std::size_t m_baseOffset = 0;
};

} // namespace rl

#endif //RLLIB_BUNDLE_HPP
