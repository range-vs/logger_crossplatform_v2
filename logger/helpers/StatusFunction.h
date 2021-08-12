#pragma once

#ifdef _WIN32
    #include <windows.h>
#endif

#include "../logger/logger/log.h"
#include "../stacktrace/StackTraceSingleton.h"

namespace stat_func
{
    bool checkExpression(bool expression);
#ifdef WIN32
    bool checkExpression(HRESULT expression);
#endif
}

namespace init_logger
{
    #if defined(_WIN32) || defined(_LINUX) || defined(TARGET_OS_MAC)
        void _logger_init(const std::string& path);
    #elif __ANDROID__ 
        void _logger_init(JNIEnv* env, jobject activity, const std::string& path);
    #endif
}

#if defined(_WIN32) || defined(_LINUX) || defined(TARGET_OS_MAC)
    #define logger_init(path) { init_logger::_logger_init(path); }
#elif __ANDROID__ 
    #define logger_init(env, activity, path) init_logger:_logger_init(env, activity, path);
#endif

#define printMessage(...) log_debug(__VA_ARGS__);

#define printCriticalError(...) \
{\
    log_critical_error(__VA_ARGS__, "\n" + StackTraceSingleton::getInstance()->getStacktrace()); \
    std::exit(-1);\
}

#define printError(...) \
{\
    log_error(__VA_ARGS__, "\n" + StackTraceSingleton::getInstance()->getStacktrace()); \
}

#define printWarning(...) log_warning(__VA_ARGS__);

#define checkError(expression, ...)\
{\
    if (stat_func::checkExpression(expression))\
       log_error(__VA_ARGS__, "\n" + StackTraceSingleton::getInstance()->getStacktrace()); \
}


#define checkCriticalError(expression, ...)\
{\
    if (stat_func::checkExpression(expression))\
    {\
        log_critical_error(__VA_ARGS__, "\n" + StackTraceSingleton::getInstance()->getStacktrace()); \
        std::exit(-1);\
    }\
}

#define checkWarning(expression, ...)\
{\
    if (stat_func::checkExpression(expression))\
       log_warning(__VA_ARGS__); \
}
