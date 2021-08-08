#pragma once

#ifdef __ANDROID__
#include <iostream>
#include <iomanip>

#include <unwind.h>
#include <dlfcn.h>

class StackWalkerAndroid
{
    struct BacktraceState
    {
        void **current;
        void **end;
    };

    static _Unwind_Reason_Code unwindCallback(struct _Unwind_Context *context, void *arg);
    size_t captureBacktrace(void** buffer, size_t max);
public:

    void dumpBacktrace(std::ostream& os, void** buffer, size_t max);
};
#endif