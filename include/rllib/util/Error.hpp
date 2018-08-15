#ifndef RLLIB_ERROR_HPP
#define RLLIB_ERROR_HPP

#include <string>

#ifdef NDEBUG
#define RL_ASSERT(exp, msg) ((void) 0)
#else
#define RL_ASSERT(exp, msg) if (!(exp)) rl::abort((msg), #exp, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#endif

namespace rl
{

void abort(const std::string & msg, const char * exp, const char * func, const char * file, unsigned line);

} // namespace rl

#endif //RLLIB_ERROR_HPP
