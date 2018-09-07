#ifndef RLLIB_ENTITYINFO_HPP
#define RLLIB_ENTITYINFO_HPP

#include <cstddef>

namespace rl
{

/**
 * Structure representing the location of an entity in a scene file.
 */
struct RL_API EntityLocation
{
    /**
     * The offset where the entity data starts.
     */
    std::size_t offset = 0;
    
    /**
     * The length of the entity data.
     */
    std::size_t size = 0;
};

} // namespace rl

#endif //RLLIB_ENTITYINFO_HPP
