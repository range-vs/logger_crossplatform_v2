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

#ifdef _WIN32
#define logger_init(pathToLog)\
{\
    std::shared_ptr<VisualStudioOutput> visualStudioOutput(std::make_shared<VisualStudioOutput>()); \
    std::shared_ptr<WinAPIOutput> winApiOutput(std::make_shared<WinAPIOutput>()); \
    std::shared_ptr<HTMLFileOutput> htmlFileOutput(std::make_shared<HTMLFileOutput>()); \
    htmlFileOutput->setPathFile(pathToLog); \
    std::shared_ptr<TerminalOutput> terminalOutput(std::make_shared<TerminalOutput>()); \
    log_init("alien engine", "0.0.1", htmlFileOutput, terminalOutput, visualStudioOutput, winApiOutput); \
}
#elif __ANDROID__ 
#define logger_init(env, activity, pathToLog)\
{\
    std::shared_ptr<HTMLFileOutput> htmlFileOutput(std::make_shared<HTMLFileOutput>());\
    htmlFileOutput->setPathFile(pathToLog);\
    std::shared_ptr<AndroidLogcatOutput> androidLogcatOutput(std::make_shared<AndroidLogcatOutput>()); \
    std::shared_ptr<TerminalOutput> terminalOutput(std::make_shared<TerminalOutput>());\
    log_init("alien engine", "0.0.1", htmlFileOutput, terminalOutput, androidLogcatOutput);\
}
#endif

#define printMessage(...) log_debug(__VA_ARGS__);

#ifdef __ANDROID__
#define printCriticalError(...) \
{\
    log_critical_error(__VA_ARGS__, "\n" + StackTraceSingleton::getInstance()->getStacktrace()); \
    std::exit(-1);\
}
#else
#define printCriticalError(...) \
{\
    log_critical_error(__VA_ARGS__, "\n" + StackTraceSingleton::getInstance()->getStacktrace()); \
    std::exit(-1);\
}
#endif

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

#ifdef __ANDROID__
#define checkCriticalError(expression, ...)\
{\
    if (stat_func::checkExpression(expression))\
    {\
        log_critical_error(__VA_ARGS__, "\n" + StackTraceSingleton::getInstance()->getStacktrace()); \
        std::exit(-1);\
    }\
}
#else
#define checkCriticalError(expression, ...)\
{\
    if (stat_func::checkExpression(expression))\
    {\
        log_critical_error(__VA_ARGS__, "\n" + StackTraceSingleton::getInstance()->getStacktrace()); \
        std::exit(-1);\
    }\
}
#endif

#define checkWarning(expression, ...)\
{\
    if (stat_func::checkExpression(expression))\
       log_warning(__VA_ARGS__); \
}