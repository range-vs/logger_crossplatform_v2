#include <pch.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "WinAPIOutput.h"

#include "../helpers/time_utils.h"
#include "factory_messages/TerminalFactory.h"

void WinAPIOutput::init(const std::string& nameGame, const std::string& versionGame)
{

}

void WinAPIOutput::init(const std::wstring& nameGame, const std::wstring& versionGame)
{
	assert(false && "wide char functional not implemented!");
}

void WinAPIOutput::message(const LogType& lt, const std::string & str)
{
	if (lt == LogType::LOG_CRITICAL_ERROR)
	{
		auto messageBuilder(CreatorMessagesTerminalOutput::create(lt));
		auto msg(messageBuilder->createMessage(str) + "\nGetLastError WinAPI: " + std::to_string(GetLastError()));
		MessageBoxA(NULL, msg.c_str(), "Critical error!", MB_OK);
	}
}

void WinAPIOutput::message(const LogType& lt, const std::wstring& str)
{
	assert(false && "wide char functional not implemented!");
}

OutputType WinAPIOutput::getOutputType() const
{
	return OutputType::WIN_API;
}

WinAPIOutput::~WinAPIOutput()
{

}

#endif

