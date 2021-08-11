#pragma once

#ifdef _LINUX

#include <execinfo.h>


class StackWalkerLinux
{

public:
    static std::vector<std::string> dumpBacktrace(); 
};

#endif