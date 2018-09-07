#include "Time.hpp"

#include <rllib/Config.hpp>

#include <chrono>

#ifdef RL_OS_WINDOWS
    #include <windows.h>
    #include <sstream>
#endif

namespace rl
{

int64_t currentTime()
{
    using namespace std::chrono;
    auto time_point = time_point_cast<nanoseconds>(system_clock::now());
    int64_t time = time_point.time_since_epoch().count();
    return time / 100 + 116'444'736'000'000'000;
}

#ifdef RL_OS_WINDOWS

std::string timeToString(int64_t time)
{
    FILETIME ftime = {static_cast<DWORD>(time), static_cast<DWORD>(time >> 32)};
    
    FILETIME ltime;
    FileTimeToLocalFileTime(&ftime, &ltime);
    
    SYSTEMTIME stime;
    FileTimeToSystemTime(&ltime, &stime);
    
    std::ostringstream stream;
    stream << stime.wYear << '/' << stime.wMonth << '/' << stime.wDay << ", " << stime.wHour << ':' << stime.wMinute;
    return stream.str();
}

#else

std::string timeToString(int64_t time)
{
    return "n/a";
}

#endif

} // namespace rl
