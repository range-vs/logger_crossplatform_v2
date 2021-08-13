#include <pch.h>
#include "AppleTerminalOutput.h"


#ifdef __APPLE__

#import <Foundation/Foundation.h>

#include "../helpers/time_utils.h"

#include "factory_messages/TerminalFactory.h"

void AppleTerminalOutput::init(const std::string& nameGame, const std::string& versionGame)
{
	NSLog(@"Log for session");
    std::string data = "Time session: " + TimeUtils::getCurrentTime() + "\n" + "Name project: " + nameGame + "\n" + "Version project: " + versionGame;
    NSString* _data = [[NSString alloc] initWithUTF8String:data.c_str()];
    NSLog(@"%@", _data);
}

void AppleTerminalOutput::init(const std::wstring& nameGame, const std::wstring& versionGame)
{
	assert(false && "wide char functional not implemented!");
}

void AppleTerminalOutput::message(const LogType& lt, const std::string & str)
{
	auto messageBuilder(CreatorMessagesTerminalOutput::create(lt));
	auto msg(messageBuilder->createMessage(str));
    NSString* _data = [[NSString alloc] initWithUTF8String:msg.c_str()];
    NSLog(@"%@", _data);
}

void AppleTerminalOutput::message(const LogType& lt, const std::wstring& str)
{
	assert(false && "wide char functional not implemented!");
}

OutputType AppleTerminalOutput::getOutputType() const
{
	return OutputType::APPLE_OUTPUT;
}

AppleTerminalOutput::~AppleTerminalOutput()
{

}

#endif

