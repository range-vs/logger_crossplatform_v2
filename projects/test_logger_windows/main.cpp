#include "pch.h"
#include <string>

#include "helpers/StatusFunction.h"
#include "logger/core/helpers/WindowsFormatMessage.h"

#include <windows.h> 
#include <excpt.h>

int _WinMainImpl(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow);
int exception_filter(unsigned int code, struct _EXCEPTION_POINTERS* ep);
int error_test();
int error_test1();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow)
{
	int result(-1);
	__try
	{
		result = _WinMainImpl(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	}
	__except (exception_filter(GetExceptionCode(), GetExceptionInformation()))
	{
		std::exit(-1);
	}
	return result;
}

int _WinMainImpl(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow)
{
	// аллоцируем консоль для теста
	AllocConsole();
	FILE* stream;
	errno_t err;
	err = freopen_s(&stream, "CONOUT$", "w", stdout);
	//

	logger_init("log.html");

	printMessage("cock", 33, 45.f);
	printError("sasa");
	printWarning("as", 323);

	checkError(true, "sad", 4);
	checkWarning(true, "sadas", 443);

	error_test();
	printCriticalError("sasdasda");
	int a = 45;
	a += 89;
	checkCriticalError(true, 332, "sadas", 5);
	checkCriticalError(true, 332, "sadas", 5);
	return 0;
}

int exception_filter(unsigned int code, struct _EXCEPTION_POINTERS* ep)
{
	/*if (code == EXCEPTION_ACCESS_VIOLATION)
	{
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else
	{
		return EXCEPTION_CONTINUE_SEARCH;
	};*/

	printCriticalErrorForWindowsExceptionHandling(ep->ContextRecord, "Error windows structured exception: ", 
		WindowsFormatMessage::GetErrorMessageException(code));
	return EXCEPTION_EXECUTE_HANDLER;
}

int error_test()
{
	error_test1();
	return 0;
}

int error_test1()
{
	int* a = nullptr;
	*a = 45;
	return 1;
}
