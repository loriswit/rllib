#ifndef RLLIB_SCENE_HPP
#define RLLIB_SCENE_HPP

#include <rllib/stream/ByteStream.hpp>
#include <rllib/bundle/Bundle.hpp>
#include <rllib/locator/Locators.hpp>
#include "Entity.hpp"

#include <optional>
#include <functional>

namespace rl
{

/**
 * The scene represents a world filled with entities that the game engine can run and display.
 * When the scene is loaded, it uses an algorithm function to locate all the entities.
 * The default algorithm can be replaced by another one by modifying the static variable rl::Scene::locator,
 * which is a callable object. A few algorithms are available in the namespace rl::locator.
 */
class Scene
{
public:
    /**
     * Creates an empty scene.
     */
    Scene() = default;
    
    /**
     * Creates and loads the scene from a file.
     *
     * @param path The path to the scene file
     */
    explicit Scene(const FilePath & path);
    
    /**
     * Loads the scene from a file.
     *
     * @param path The path to the scene file
     */
    void load(const FilePath & path);
    
    /**
     * Saves the scene into a file.
     *
     * @warning If the file already exists, the original content of the file will be lost.
     *
     * @param path The path to the scene file
     */
    void save(const FilePath & path) const;
    
    /**
     * Tells if the scene has an entity with the specified name.
     *
     * @param name The name of the entity
     * @return <code>true</code> if such an entity exists, <code>false</code> if not
     */
    bool hasEntity(const std::string & name) const;
    
    /**
     * Returns the number of entities in the scene.
     *
     * @return The number of entities
     */
    std::size_t entityCount() const noexcept;
    
    /**
     * Returns the entity (const) associated to the given name.
     * If there is no such entity, the behavior is undefined.
     *
     * @note Entities names don't have to be unique, even though they usually are in practice.
     * If a scene contains multiple entities with the same name, only the first occurrence is returned.
     *
     * @warning This function should be used primarily for testing, since entities names are not
     * identifiers and may change during runtime. Consider using iterators (rl::Scene::begin and
     * rl::Scene::end) or the access-by-index operator (rl::Scene::operator[](std::size_t)).
     *
     * @param name The name of the entity
     * @return A reference to the entity (const).
     */
    const Entity & operator[](const std::string & name) const;
    
    /**
     * Returns the entity associated to the given name.
     * If there is no such entity, the behavior is undefined.
     *
     * @note Entities names don't have to be unique, even though they usually are in practice.
     * If a scene contains multiple entities with the same name, only the first occurrence is returned.
     *
     * @warning This function should be used primarily for testing, since entities names are not
     * identifiers and may change during runtime. Consider using iterators (rl::Scene::begin and
     * rl::Scene::end) or the access-by-index operator (rl::Scene::operator[](std::size_t)).
     *
     * @param name The name of the entity
     * @return A reference to the entity
     */
    Entity & operator[](const std::string & name);
    
    /**
     * Returns the entity (const) at the given index.
     * If the index is out of bound, the behavior is undefined.
     *
     * @param index The entity index
     * @return A reference to the entity (const)
     */
    const Entity & operator[](std::size_t index) const;
    
    /**
     * Returns the entity at the given index.
     * If the index is out of bound, the behavior is undefined.
     *
     * @param index The entity index
     * @return A reference to the entity
     */
    Entity & operator[](std::size_t index);
    
    /**
     * @return An iterator pointing to the first entity
     */
    std::vector<Entity>::iterator begin() noexcept;
    
    /**
     * @return An iterator pointing to the first entity (const)
     */
    std::vector<Entity>::const_iterator cbegin() const noexcept;
    
    /**
     * @return An iterator pointing to the last entity
     */
    std::vector<Entity>::iterator end() noexcept;
    
    /**
     * @return An iterator pointing to the last entity (const)
     */
    std::vector<Entity>::const_iterator cend() const noexcept;
    
    /**
     * Some unknown properties that might be specific to this scene.
     */
    ByteStream header;
    
    /**
     * Function that locates entities using a specific strategy.
     */
    static std::function<std::vector<EntityLocation>(ByteStream &)> locator;
    
    SERIALIZABLE

private:
    /**
     * Finds the first entity with the specified name.
     *
     * @param name The name of the entity
     * @return A reference to the entity if found, or no value
     */
    std::optional<std::reference_wrapper<Entity>> findEntity(const std::string & name);
    
    /**
     * Finds the first entity (const) with the specified name.
     *
     * @param name The name of the entity
     * @return A reference to the entity (const) if found, or no value
     */
    std::optional<std::reference_wrapper<const Entity>> findEntity(const std::string & name) const;
    
    std::vector<Entity> m_entities;
};

} // namespace rl

#endif //RLLIB_SCENE_HPP
