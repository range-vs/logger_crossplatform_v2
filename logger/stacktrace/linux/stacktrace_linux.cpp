#include <pch.h>

#include "stacktrace_linux.h"

#ifdef _LINUX

std::vector<std::string> StackWalkerLinux::dumpBacktrace()
{
    std::vector<std::string> result;
    void* stack[512];
    int stack_size = ::backtrace(stack, sizeof stack / sizeof *stack);
    char **strings = backtrace_symbols(stack, stack_size);
    for(int i(0); i < stack_size; ++i)
        result.emplace_back(static_cast<char*>(strings[i]));
    free(strings);
    return result;
}

#endif
