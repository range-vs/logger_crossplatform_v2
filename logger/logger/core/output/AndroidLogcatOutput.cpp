#include <pch.h>
#include "AndroidLogcatOutput.h"

#ifdef __ANDROID__ 

#include <android/log.h>

#include "../helpers/time_utils.h"

#include "factory_messages/TerminalFactory.h"

constexpr const char* LogCatAppName = "LOGGER_OUTPUT";

void AndroidLogcatOutput::init(const std::string& nameGame, const std::string& versionGame)
{
	__android_log_print(ANDROID_LOG_VERBOSE, LogCatAppName, "Log for session");
	__android_log_print(ANDROID_LOG_VERBOSE, LogCatAppName, "%s", std::string("Time session: " + TimeUtils::getCurrentTime()).c_str());
	__android_log_print(ANDROID_LOG_VERBOSE, LogCatAppName, "%s", std::string("Name project: " + nameGame).c_str());
	__android_log_print(ANDROID_LOG_VERBOSE, LogCatAppName, "%s", std::string("Version project: " + versionGame).c_str());
}

void AndroidLogcatOutput::init(const std::wstring& nameGame, const std::wstring& versionGame)
{
	assert(false && "wide char functional not implemented!");
}

void AndroidLogcatOutput::message(const LogType& lt, const std::string & str)
{
	auto messageBuilder(CreatorMessagesTerminalOutput::create(lt));
	auto msg(messageBuilder->createMessage(str));
	__android_log_print(ANDROID_LOG_VERBOSE, LogCatAppName, "%s", msg.c_str());

}

void AndroidLogcatOutput::message(const LogType& lt, const std::wstring& str)
{
	assert(false && "wide char functional not implemented!");
}

OutputType AndroidLogcatOutput::getOutputType() const
{
	return OutputType::ANDROID_LOGCAT;
}

AndroidLogcatOutput::~AndroidLogcatOutput()
{

}

#endif

