#include <pch.h>
#include "MacOutput.h"


#ifdef __APPLE__

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include "../helpers/time_utils.h"

#include "factory_messages/TerminalFactory.h"

void MacOutput::init(const std::string& nameGame, const std::string& versionGame)
{

}

void MacOutput::init(const std::wstring& nameGame, const std::wstring& versionGame)
{
	assert(false && "wide char functional not implemented!");
}

void MacOutput::message(const LogType& lt, const std::string & str)
{
    if(lt == LogType::LOG_CRITICAL_ERROR)
    {
        auto messageBuilder(CreatorMessagesTerminalOutput::create(lt));
        auto msg(messageBuilder->createMessage(str));
        NSString* _data = [[NSString alloc] initWithUTF8String:msg.c_str()];
        NSAlert* alert = [[NSAlert alloc] init];
        [alert setMessageText:@"Fatal error"];
        [alert setInformativeText:_data];
        [alert addButtonWithTitle:@"OK"];
        [alert setAlertStyle:NSAlertStyleWarning];
        [alert runModal];
    }
}

void MacOutput::message(const LogType& lt, const std::wstring& str)
{
	assert(false && "wide char functional not implemented!");
}

OutputType MacOutput::getOutputType() const
{
	return OutputType::MAC_OUTPUT;
}

MacOutput::~MacOutput()
{

}

#endif

