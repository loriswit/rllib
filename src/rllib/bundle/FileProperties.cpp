#include <rllib/bundle/FileProperties.hpp>
#include "../util/Time.hpp"

#include <stdexcept>

namespace rl
{

FileProperties::FileProperties()
{
    touch();
}

void FileProperties::touch()
{
    time = currentTime();
}

} // namespace rl
