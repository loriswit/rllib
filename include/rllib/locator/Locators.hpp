#ifndef RLLIB_NAMESTRATEGY_HPP
#define RLLIB_NAMESTRATEGY_HPP

#include <rllib/stream/ByteStream.hpp>
#include "EntityLocation.hpp"

#include <vector>

/**
 * Namespace containing functions that locate entities segments in scene files.
 */
namespace rl::locator
{

/**
 * Locates entities by looking for strings that are probably their names.
 * This is the default algorithm and also the fastest.
 *
 * @param data The scene data
 * @return The list containing the entities locations
 */
std::vector<EntityLocation> names(ByteStream & data);

/**
 * Locates entities by looking for patterns of values around their names.
 *
 * @param data The scene data
 * @return The list containing the entities locations
 */
std::vector<EntityLocation> values(ByteStream & data);

} // namespace rl

#endif //RLLIB_NAMESTRATEGY_HPP
