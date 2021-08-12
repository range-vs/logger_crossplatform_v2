#pragma once

#if __linux__ || __APPLE__

#include <execinfo.h>


class StackWalkerLinux
{

public:
    static std::vector<std::string> dumpBacktrace(); 
};

#endif
