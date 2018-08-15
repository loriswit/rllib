#ifndef RLLIB_TEMP_HPP
#define RLLIB_TEMP_HPP

#include <rllib/stream/ByteStream.hpp>

#define SERIALIZE_DECL ByteStream serialize() const
#define DESERIALIZE_DECL void deserialize(ByteStream & buf)
#define OP_BYTESTREAM operator ByteStream() const { return serialize(); }

#define SERIALIZE(...) \
    SERIALIZE_DECL { return rl::serializeArgs(__VA_ARGS__); } \
    DESERIALIZE_DECL { rl::deserializeArgs(buf, __VA_ARGS__); } \
    OP_BYTESTREAM

#define SERIALIZABLE SERIALIZE_DECL; DESERIALIZE_DECL; OP_BYTESTREAM

namespace rl
{

template<typename... Args>
inline ByteStream serializeArgs(Args && ... args)
{
    return (ByteStream() << ... << args);
}

template<typename... Args>
inline void deserializeArgs(ByteStream & buf, Args && ... args)
{
    (buf >> ... >> args);
}

} // namespace rl

#endif //RLLIB_TEMP_HPP
