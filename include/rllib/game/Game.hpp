#ifndef RLLIB_GAME_HPP
#define RLLIB_GAME_HPP

#include <rllib/bundle/Bundle.hpp>
#include "Scene.hpp"

namespace rl
{

/**
 * This class represents the game itself.
 * It provides features to extract, patch or run scenes in the game engine.
 */
class Game
{
public:
    /**
     * Creates and loads the game from the specified path.
     *
     * @param path The path to the game executable file
     */
    explicit Game(FilePath path);
    
    /**
     * Loads the game from the specified path.
     *
     * @param path The path to the game executable file
     */
    void load(FilePath path);
    
    /**
     * Returns the bundle file associated with the game.
     *
     * @return A reference to the game bundle
     */
    Bundle & getBundle() noexcept;
    
    /**
     * Extracts an asset from the game files.
     *
     * @param path The path to the asset
     * @return The extracted asset
     */
    ByteStream getAsset(const FilePath & path);
    
    /**
     * Returns a scene loaded from an asset.
     * Use rl::Game::updateAsset or rl::Game::patchAsset to overwrite or patch the scene.
     *
     * @param path The path to the asset
     * @return The scene loaded from the file
     */
    Scene getScene(const FilePath & path);
    
    /**
     * Overwrites an asset in the game files.
     * The file path to the asset must already exist.
     *
     * @warning The original asset will be lost. Consider <b>patching</b> the asset
     * if you wish to keep the original content unchanged (see rl::Game::patchAsset).
     *
     * @param path The path to the asset
     * @param data The asset data
     */
    void updateAsset(const FilePath & path, const ByteStream & data);
    
    /**
     * Creates a patch for a specific asset, leaving the original content unmodified.
     * Use rl::Game::removePatch to revert the changes.
     *
     * @note Only a single file can be patched at once.
     * Calling this function a second time will remove the previous patch.
     *
     * @param path The path to the scene file
     * @param data The scene object
     */
    void patchAsset(const FilePath & path, const ByteStream & data);
    
    /**
     * Deletes the current existing patch.
     */
    void removePatch();
    
    /**
     * Launches a specific scene in the game engine and displays the logs.
     * If the specified scene does not exists, the game is launched normally.
     *
     * @warning This function might not work with all versions of the game,
     * since some of them require the game to be launched by Steam or Uplay.
     * For now, the only workaround is to patch the home scene and launch
     * the game normally:
     * @code
     * auto scene = game.getScene(path);
     * patchScene("world/home/level/home.isc", scene);
     * game.run();
     * @endcode
     *
     * @param path The path to the scene file
     * @return The exit code status
     */
    int run(const FilePath & path = "");
    
    /**
     * Launches the given scene in the game engine and displays the logs.
     *
     * @warning This function might not work with all versions of the game,
     * since some of them require the game to be launched by Steam or Uplay.
     * For now, the only workaround is to patch the home scene and launch
     * the game normally:
     * @code
     * patchScene("world/home/level/home.isc", scene);
     * game.run();
     * @endcode
     *
     * @param scene The scene object
     * @return The exit code status
     */
    int run(const Scene & scene);
    
private:
    FilePath m_path;
    
    Bundle m_bundle;
};

} // namespace rl

#endif //RLLIB_GAME_HPP
