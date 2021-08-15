#pragma once

#ifdef _WIN32

#include <Windows.h>
#include <system_error>
#include <memory>
#include <string>

#include <Winternl.h>
#pragma comment(lib, "ntdll.lib")

namespace WindowsFormatMessage
{
    std::string GetErrorMessage(DWORD dwErrorCode); // get last error
    const char* GetErrorMessageException(unsigned int code); // windows struct exceptions
}

#endif