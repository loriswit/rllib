#include <rllib/game/Game.hpp>

#include <iostream>

namespace
{

constexpr auto BUNDLE_FILENAME = "Bundle_PC.ipk";
constexpr auto PATCH_FILENAME = "patch_PC.ipk";
constexpr auto SCENE_PATH = "rllib/scene.isc";
constexpr auto CACHE_DIRECTORY = "cache/itf_cooked/pc/";
constexpr auto ASSET_EXT = ".ckd";

}

namespace rl
{

Game::Game(FilePath path)
{
    load(std::move(path));
}

void Game::load(FilePath path)
{
    m_path = std::move(path);
    m_bundle.load({m_path.directory, BUNDLE_FILENAME});
}

Bundle & Game::getBundle() noexcept
{
    return m_bundle;
}

ByteStream Game::getAsset(const FilePath & path)
{
    return m_bundle.readFile(CACHE_DIRECTORY + path + ASSET_EXT);
}

Scene Game::getScene(const FilePath & path)
{
    return getAsset(path).get<Scene>();
}

void Game::updateAsset(const FilePath & path, const ByteStream & data)
{
    m_bundle.writeFile(CACHE_DIRECTORY + path + ASSET_EXT, data);
}

void Game::patchAsset(const FilePath & path, const ByteStream & data)
{
    Bundle::create(m_path.directory + PATCH_FILENAME, {
            {CACHE_DIRECTORY + path + ASSET_EXT, data}
    });
}

void Game::removePatch()
{
    FilePath path(m_path.directory, PATCH_FILENAME);
    if(std::remove(std::string(path).c_str()))
        throw std::runtime_error("could not remove patch file " + path);
}

int Game::run(const FilePath & path)
{
    std::string cmdLine = "cd " + m_path.directory
            + " && \"" + m_path.filename + "\" map=" + path;
    
    auto stream = popen(cmdLine.c_str(), "r");
    if(!stream)
        throw std::runtime_error("could not run command " + cmdLine);
    
    std::cout << "Starting game " << m_path << std::endl;
    
    constexpr int LINE_MAX = 256;
    std::array<char, LINE_MAX> buffer;
    while(fgets(buffer.data(), LINE_MAX, stream))
        std::cout << "> " << buffer.data() << std::flush;
    
    auto status = pclose(stream);
    std::cout << "Game exited with code " << std::hex << std::showbase << status << std::endl;
    
    return status;
}

int Game::run(const Scene & scene)
{
    patchAsset(SCENE_PATH, scene);
    return run(SCENE_PATH);
}

} // namespace rl
