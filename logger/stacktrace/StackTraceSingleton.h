#pragma once

#ifdef _WIN32
#include "windows/StackWalker.h"
#elif __ANDROID__ 
#include "android/stacktrace_android.h"
#elif __linux__ || __APPLE__
#include "linux/stacktrace_linux.h"
#endif

class StackTraceSingleton
{
#ifdef _WIN32
    class StackWalkerToString : public StackWalker
    {
        std::string buffer;
    protected:
        virtual void OnOutput(LPCSTR szText);
    public:
        std::string getStackTrace();
    };
    StackWalkerToString sw;
    std::string getStacktraceForWindows();
#elif __ANDROID__
    StackWalkerAndroid swa;
#endif

    static std::unique_ptr<StackTraceSingleton> instance;

    std::vector<std::string> splitter(const std::string in_pattern, const std::string& content);
public:
    StackTraceSingleton() = default;
    StackTraceSingleton(const StackTraceSingleton&) = delete;
    void operator=(const StackTraceSingleton&) = delete;
    StackTraceSingleton(const StackTraceSingleton&&) = delete;
    void operator=(StackTraceSingleton&&) = delete;
    ~StackTraceSingleton() = default;

    static std::unique_ptr<StackTraceSingleton>& getInstance();

    std::string getStacktrace();

};
