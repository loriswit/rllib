#include <rllib/locator/Locators.hpp>
#include "Helpers.hpp"

namespace rl::locator
{

std::vector<EntityLocation> names(ByteStream & data)
{
    std::vector<EntityLocation> entityList;
    std::size_t next = 0;
    
    const std::regex regex(R"(\w{3,}(@\d+)?)");
    for(auto it = regexBegin(data, regex); it != regexEnd(); ++it)
    {
        auto offset = static_cast<std::size_t>(it->position() - 0x18);
        
        if(offset < next)
            continue;
        
        // name size must be equal to the length of the string
        auto nameSize = data.get<uint32_t>(offset + 0x14);
        if(nameSize != it->str().size())
            continue;
        
        // entity must have valid floats values (not to big, not to small, not nan)
        if(!validEntity(data, offset))
            continue;
        
        next = data.tell();
        
        if(!entityList.empty())
            entityList.back().size = offset - entityList.back().offset;
        
        entityList.push_back({offset});
    }
    
    if(!entityList.empty())
        entityList.back().size = data.size() - entityList.back().offset;
    
    return entityList;
}

std::vector<EntityLocation> values(ByteStream & data)
{
    std::vector<EntityLocation> entityList;
    
    const std::regex regex(R"(\x00\x00\x00(\x00|\x01)[\s\S]{4}([\w@]+))"
                           R"(\x00\x00\x00\x00[\s\S]{12}\x00\x00\x00\x00)"
                           R"(\x00\x00\x00\x00\xff\xff\xff\xff\x00\x00\x00\x00)");
    
    for(auto it = regexBegin(data, regex); it != regexEnd(); ++it)
    {
        auto offset = static_cast<std::size_t>(it->position() - 0x10);
    
        if(!entityList.empty())
            entityList.back().size = offset - entityList.back().offset;
    
        // name size must be equal to the length of the string
        auto nameSize = data.get<uint32_t>(offset + 0x14);
        if(nameSize != it->str(2).size())
            continue;
    
        // entity must have valid floats values (not to big, not to small, not nan)
        if(!validEntity(data, offset))
            continue;
        
        entityList.push_back({offset});
    }
    
    if(!entityList.empty())
        entityList.back().size = data.size() - entityList.back().offset;
    
    return entityList;
}

} // namespace rl
