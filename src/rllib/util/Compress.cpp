#include "Compress.hpp"

#include <zlib.h>

namespace rl
{

ByteStream deflate(const ByteStream & in)
{
    z_stream defStr;
    defStr.zalloc = Z_NULL;
    defStr.zfree = Z_NULL;
    defStr.opaque = Z_NULL;
    defStr.avail_in = static_cast<uInt>(in.size());
    defStr.next_in = const_cast<Bytef *>(in.data());
    
    deflateInit(&defStr, Z_DEFAULT_COMPRESSION);
    
    auto defMaxSize = deflateBound(&defStr, static_cast<uLong>(in.size()));
    ByteStream out(defMaxSize);
    defStr.avail_out = static_cast<uInt>(out.size());
    defStr.next_out = out.data();
    
    deflate(&defStr, Z_FINISH);
    deflateEnd(&defStr);
    
    out.resize(defStr.total_out);
    return out;
}

ByteStream inflate(const ByteStream & in, std::size_t outSize)
{
    z_stream infStr;
    infStr.zalloc = Z_NULL;
    infStr.zfree = Z_NULL;
    infStr.opaque = Z_NULL;
    infStr.avail_in = static_cast<uInt>(in.size());
    infStr.next_in = const_cast<Bytef *>(in.data());
    
    inflateInit(&infStr);
    
    ByteStream out(outSize);
    infStr.avail_out = static_cast<uInt>(out.size());
    infStr.next_out = out.data();
    
    inflate(&infStr, Z_NO_FLUSH);
    inflateEnd(&infStr);
    
    return out;
}

} // namespace rl
