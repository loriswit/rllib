#include <rllib/util/FilePath.hpp>

namespace
{

std::string normalize(std::string path)
{
    std::replace(path.begin(), path.end(), '\\', '/');
    return path;
}

std::string withTrailingSlash(std::string path)
{
    if(!path.empty() && path.back() != '/')
        path += '/';
    
    return path;
}

} // namespace

namespace rl
{

FilePath::FilePath(const std::string & dir, const std::string & name)
{
    directory = withTrailingSlash(normalize(dir));
    filename = normalize(name);
}

FilePath::FilePath(const std::string & path)
{
    auto normalized = normalize(path);
    auto split = normalized.find_last_of('/') + 1;
    
    directory = withTrailingSlash(normalized.substr(0, split));
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
