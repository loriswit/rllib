#ifndef RLLIB_COMPRESS_HPP
#define RLLIB_COMPRESS_HPP

#include <rllib/stream/ByteStream.hpp>

namespace rl
{

/**
 * Compresses a data stream using zlib.
 *
 * @param in The input data stream
 * @return The compressed data
 */
ByteStream deflate(const ByteStream & in);

/**
 * Decompresses a data stream using zlib.
 *
 * @param in The input data stream
 * @param outSize The size of the decompressed data
 * @return The decompressed data
 */
ByteStream inflate(const ByteStream & in, std::size_t outSize);

} // namespace rl

#endif //RLLIB_COMPRESS_HPP
