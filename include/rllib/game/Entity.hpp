#ifndef RLLIB_ENTITY_HPP
#define RLLIB_ENTITY_HPP

#include <rllib/stream/Serializable.hpp>
#include <rllib/util/Vector3.hpp>
#include <rllib/util/Vector2.hpp>
#include <rllib/util/Angle.hpp>

#include <array>

namespace rl
{

/**
 * An entity represents anything present in the scene, such as platforms, items, cameras, sounds, lights, etc.
 * Each entity starts with common properties (name, position, scale, rotation) and is then followed by
 * some data of variable length that contains properties specific to each entity.
 */
struct Entity
{
    /**
     * An unknown property that starts the entity data.
     */
    int32_t header;
    
    /**
     * The name of the entity.
     *
     * @warning The name is not unique to the entity. It can be changed to anything
     * (even an empty string) without changing the entity appearance or behaviour.
     * Changing the name is however <b>not advised</b> because the entities location
     * algorithms are looking for names, and may fail to find this entity in the future.
     */
    std::string name;
    
    /**
     * The position of the entity.
     */
    Vector3f position;
    
    /**
     * The size scale of the entity.
     */
    Vector2f scale;
    
    /**
     * The rotation of the entity.
     */
    Angle rotation;
    
    /**
     * Some unknown properties that are common for every entities.
     */
    std::array<int32_t, 6> unknown;
    
    /**
     * Some data containing properties that are specific to this entity.
     */
    ByteStream data;
    
    SERIALIZE(header, position.z, scale.x, scale.y, unknown[0],
              name, unknown[1], position.x, position.y,
              rotation.angle, unknown[2], unknown[3],
              unknown[4], unknown[5], data)
};

} // namespace rl

#endif //RLLIB_ENTITY_HPP
