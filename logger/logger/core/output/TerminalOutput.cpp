#include <pch.h>
#include <string>
#include "TerminalOutput.h"

#include "../helpers/time_utils.h"
#include <sstream>
#include <algorithm>
#include <regex>
#include <iostream>

#include "factory_messages/TerminalFactory.h"

void TerminalOutput::init(const std::string& nameGame, const std::string& versionGame)
{
	std::cout << "Log for session" << std::endl;
	std::cout << "Time session: " << TimeUtils::getCurrentTime() << std::endl;
	std::cout << "Name project: " << nameGame << std::endl;
	std::cout << "Version project: " << versionGame << std::endl;
}

void TerminalOutput::init(const std::wstring& nameGame, const std::wstring& versionGame)
{
	assert(false && "wide char functional not implemented!");
}

void TerminalOutput::message(const LogType& lt, const std::string & str)
{
	auto messageBuilder(CreatorMessagesTerminalOutput::create(lt));
	std::cout << messageBuilder->createMessage(str);
}

void TerminalOutput::message(const LogType& lt, const std::wstring& str)
{
	assert(false && "wide char functional not implemented!");
}

OutputType TerminalOutput::getOutputType() const
{
	return OutputType::TERMINAL;
}

TerminalOutput::~TerminalOutput()
{

}

