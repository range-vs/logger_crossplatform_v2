#include <pch.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "VisualStudioOutput.h"

#include "../helpers/time_utils.h"

#include "factory_messages/TerminalFactory.h"

void VisualStudioOutput::init(const std::string& nameGame, const std::string& versionGame)
{
	OutputDebugStringA("Log for session\n");
	OutputDebugStringA(std::string("Time session: " + TimeUtils::getCurrentTime() + "\n").c_str());
	OutputDebugStringA(std::string("Name project: " + nameGame + "\n").c_str());
	OutputDebugStringA(std::string("Version project: " + versionGame + "\n").c_str());
}

void VisualStudioOutput::init(const std::wstring& nameGame, const std::wstring& versionGame)
{
	assert(false && "wide char functional not implemented!");
}

void VisualStudioOutput::message(const LogType& lt, const std::string & str)
{
	auto messageBuilder(CreatorMessagesTerminalOutput::create(lt));
	auto msg(messageBuilder->createMessage(str) + "GetLastError WinAPI: " + std::to_string(GetLastError()) + "\n");
	OutputDebugStringA(msg.c_str());
}

void VisualStudioOutput::message(const LogType& lt, const std::wstring& str)
{
	assert(false && "wide char functional not implemented!");
}

OutputType VisualStudioOutput::getOutputType() const
{
	return OutputType::VISUAL_STUDIO;
}

VisualStudioOutput::~VisualStudioOutput()
{

}

#endif

