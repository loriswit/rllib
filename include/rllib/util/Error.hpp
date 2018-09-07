#ifndef RLLIB_ERROR_HPP
#define RLLIB_ERROR_HPP

#include <rllib/Config.hpp>

#include <string>

#ifdef RL_DEBUG
    #define RL_ASSERT(exp, msg) if (!(exp)) rl::abort((msg), #exp, RL_FUNCTION, __FILE__, __LINE__)
#else
    #define RL_ASSERT(exp, msg) ((void) 0)
#endif

namespace rl
{

void abort(const std::string & msg, const char * exp, const char * func, const char * file, unsigned line);

} // namespace rl

#endif //RLLIB_ERROR_HPP
