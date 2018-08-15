#ifndef RLLIB_HELPERS_HPP
#define RLLIB_HELPERS_HPP

#include <rllib/stream/ByteStream.hpp>

#include <cstddef>
#include <cmath>
#include <regex>

namespace rl
{

/**
 * Returns a regex iterator for the given data stream.
 *
 * @param data The data stream to parse
 * @param regex The regular expression
 * @return The regex iterator pointing at the beginning
 */
inline std::cregex_iterator regexBegin(const ByteStream & data, const std::regex & regex);

/**
 * Returns the ending regex iterator.
 *
 * @return The regex iterator pointing at the end
 */
inline std::cregex_iterator regexEnd();

/**
 * Tells if the entity at the given offset has values that seem correct.
 * Specifically, it checks if float values of known properties (position, scale, rotation)
 * don't have a exponent either too big or too small.
 *
 * @param data The data that contains the entity
 * @param offset The offset where the entity data starts
 * @return <code>true</code> all the values seem correct, <code>false</code> if not
 */
inline bool validEntity(ByteStream & data, std::size_t offset);

#include "Helpers.inl"

} // namespace rl

#endif //RLLIB_HELPERS_HPP
