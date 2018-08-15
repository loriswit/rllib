#include <rllib/util/FilePath.hpp>

namespace
{

std::string normalize(const std::string & dir)
{
    auto directory = dir;
    
    std::replace(directory.begin(), directory.end(), '\\', '/');
    if(!directory.empty() && directory.back() != '/')
        directory += '/';
    
    return directory;
}

} // namespace

namespace rl
{

FilePath::FilePath(std::string dir, std::string name)
{
    directory = std::move(dir);
    filename = std::move(name);
    
    directory = normalize(directory);
}

FilePath::FilePath(const std::string & path)
{
    auto split = path.find_last_of('/') + 1;
    
    directory = normalize(path.substr(0, split));
    filename = path.substr(split);
}

FilePath::FilePath(const char * path) : FilePath(std::string(path))
{
}

FilePath::operator std::string() const
{
    return directory + filename;
}

bool FilePath::operator==(const FilePath & other) const noexcept
{
    return directory == other.directory && filename == other.filename;
}

std::string operator+(const std::string & str, const FilePath & path)
{
    return str + path.directory + path.filename;
}

std::ostream & operator<<(std::ostream & stream, const FilePath & path)
{
    return stream << path.directory << path.filename;
}

} // namespace rl
