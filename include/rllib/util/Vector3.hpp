#ifndef RLLIB_VECTOR3_HPP
#define RLLIB_VECTOR3_HPP

#include <ostream>

namespace rl
{

/**
 * Structure representing a three-dimensional vector.
 *
 * @tparam T The type of the vector components
 */
template<typename T>
struct RL_API Vector3
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
     * The depth component of the vector.
     */
    T z;
    
    /**
     * Creates a 3D vector.
     *
     * @param X The horizontal component of the vector
     * @param Y The vertical component of the vector
     * @param Z The depth component of the vector
     */
    constexpr Vector3(T X = 0, T Y = 0, T Z = 0);
};

/**
 * Writes the 3D vector components into a stream.
 *
 * @tparam T The type of the vector components
 * @param stream The stream object
 * @param vector The 3D vector object
 * @return The current stream
 */
template<typename T>
std::ostream & operator<<(std::ostream & stream, const Vector3<T> & vector);

/**
 * Type representing a 3D vector with float components.
 */
using Vector3f = Vector3<float>;

#include "Vector3.inl"

} // namespace rl


#endif //RLLIB_VECTOR3_HPP
