#include <rllib/util/Error.hpp>

#include <iostream>

namespace rl
{

void abort(const std::string & msg, const char * exp, const char * func, const char * file, unsigned line)
{
    std::cerr << "Assertion failed: " << msg << '\n';
    std::cerr << "Expression: " << exp << '\n';
    std::cerr << "In: " << func << '\n';
    std::cerr << "At: " << file << ':' << line << std::endl;
    std::abort();
}

} // namespace rl
