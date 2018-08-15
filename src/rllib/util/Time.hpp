#ifndef RLLIB_TIME_HPP
#define RLLIB_TIME_HPP

#include <string>
#include <cstdint>

namespace rl
{

/**
 * Returns a 64-bit timestamp of the current time.
 *
 * @return The number of 100-nanosecond intervals since January 1, 1601 (UTC)
 */
int64_t currentTime();

/**
 * Converts a 64-bit timestamp into a human-readable string.
 *
 * @param time The number of 100-nanosecond intervals since January 1, 1601 (UTC)
 * @return A human-readable string containing the date and time
 */
std::string timeToString(int64_t time);

} // namespace rl

#endif //RLLIB_TIME_HPP
