inline std::cregex_iterator regexBegin(const ByteStream & data, const std::regex & regex)
{
    auto begin = reinterpret_cast<const char *>(data.data());
    auto end = reinterpret_cast<const char *>(data.data() + data.size());
    return std::cregex_iterator(begin, end, regex);
}

inline std::cregex_iterator regexEnd()
{
    return std::cregex_iterator();
}

inline bool validEntity(ByteStream & data, std::size_t offset)
{
    auto validFloat = [](float f)
    {
        return std::fabs(f) == 0 ||
               (!std::isnan(f) &&
                std::fabs(f) < 100000 &&
                std::fabs(f) > 0.00000001);
    };
    
    data.seek(offset + 0x4);
    
    // check position.z, scale.x, scale.y
    if(!(validFloat(data.get<float>()) &&
         validFloat(data.get<float>()) &&
         validFloat(data.get<float>())))
        return false;
    
    data.get<uint32_t>();
    data.get<std::string>();
    data.get<uint32_t>();
    
    // check position.x, position.y, rotation.angle
    return validFloat(data.get<float>()) &&
           validFloat(data.get<float>()) &&
           validFloat(data.get<float>());
}
