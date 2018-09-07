#ifndef RLLIB_ANGLE_HPP
#define RLLIB_ANGLE_HPP

#include <ostream>

namespace rl
{

/**
 * The pi constant
 */
constexpr long double PI = 3.141592653589793238463;

/**
 * Class representing an angle in radian.
 *
 * @code
 * rl::Angle a = 1,5708; // constructs an angle in radian
 * rl::Angle b = 90_deg; // constructs an angle in degrees
 * @endcode
 */
struct RL_API Angle
{
    /**
     * The angle in radians.
     */
    float angle = 0;
    
    constexpr Angle() = default;
    
    /**
     * Creates an angle.
     *
     * @param a The angle in radians
     */
    constexpr Angle(float a) noexcept;
    
    /**
     * Casts the angle into a floating point value.
     *
     * @return The angle in radians
     */
    constexpr operator float() const noexcept;
    
    /**
     * Returns a reference to the angle as a floating point value.
     *
     * @return A reference to the angle in radians
     */
    constexpr operator float &() noexcept;
};

/**
 * Writes the angle in degrees into a stream.
 *
 * @param stream The stream object
 * @param angle The angle object
 * @return The current stream
 */
inline std::ostream & operator<<(std::ostream & stream, const Angle & angle);

} // namepspace rl

/**
 * Literal suffix for angles in degrees.
 *
 * @param angle The angle in degrees
 * @return The angle in radians
 */
constexpr rl::Angle operator "" _deg(long double angle);

/**
 * Literal suffix for angles in degrees.
 *
 * @param angle The angle in degrees
 * @return The angle in radians
 */
constexpr rl::Angle operator "" _deg(unsigned long long angle);

#include "Angle.inl"

#endif //RLLIB_ANGLE_HPP
