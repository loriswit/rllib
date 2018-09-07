#ifndef RLLIB_CONFIG_HPP
#define RLLIB_CONFIG_HPP

#ifdef _WIN32
    #define RL_OS_WINDOWS
#endif

#ifndef NDEBUG
    #define RL_DEBUG
#endif

#ifndef RL_STATIC
    #ifdef RL_OS_WINDOWS
        #ifdef RL_BUILD
            #define RL_API __declspec(dllexport)
        #else
            #define RL_API __declspec(dllimport)
        #endif
    #else
        #define RL_API __attribute__ ((__visibility__ ("default")))
    #endif
#else
    #define RL_API
#endif

#if defined(__GNUC__) || defined(__MINGW32__) || defined(__clang__)
    #define RL_FUNCTION __PRETTY_FUNCTION__
    #define RL_POPEN popen
    #define RL_PCLOSE pclose
#elif defined(_MSC_VER)
    #define RL_FUNCTION __FUNCSIG__
    #define RL_POPEN _popen
    #define RL_PCLOSE _pclose
    #pragma warning(disable: 4251)
#else
    #define RL_FUNCTION __func__
    #define RL_POPEN popen
    #define RL_PCLOSE pclose
#endif

#endif //RLLIB_CONFIG_HPP
