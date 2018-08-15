#ifndef RLLIB_VECTOR2_HPP
#define RLLIB_VECTOR2_HPP

#include <ostream>

namespace rl
{

/**
 * Structure representing a two-dimensional vector.
 *
 * @tparam T The type of the vector components
 */
template<typename T>
struct Vector2
{
    /**
     * The horizontal component of the vector.
     */
    T x;
    
    /**
     * The vertical component of the vector.
     */
    T y;
    
    /**
     * Creates a 2D vector.
     *
     * @param X The horizontal component of the vector
     * @param Y The vertical component of the vector
     */
    constexpr Vector2(T X = 0, T Y = 0);
};

/**
 * Writes the 2D vector components into a stream.
 *
 * @tparam T The type of the vector components
 * @param stream The stream object
 * @param vector The 2D vector object
 * @return The current stream
 */
template<typename T>
std::ostream & operator<<(std::ostream & stream, const Vector2<T> & vector);

/**
 * Type representing a 2D vector with float components.
 */
using Vector2f = Vector2<float>;

#include "Vector2.inl"

} // namespace rl

#endif //RLLIB_VECTOR2_HPP
