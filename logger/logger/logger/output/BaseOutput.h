#pragma once

#include <string>
#include "../helpers/LoggerParams.h"
#include "../messages/TypeMessages.h"
#include "../helpers/StrConsts.h"

enum class OutputType
{
	ANDROID_LOGCAT = 0,
	ANDROID_TOAST,
	HTML_FILE,
	TERMINAL,
	VISUAL_STUDIO,
	WIN_API,
    APPLE_OUTPUT,
    MAC_OUTPUT
};

class BaseOutput
{
	
public:
	virtual void init(const std::string& nameGame, const std::string& versionGame) = 0;
	virtual void init(const std::wstring& nameGame, const std::wstring& versionGame) = 0;
	virtual void message(const LogType& lt, const std::string& str) = 0;
	virtual void message(const LogType& lt, const std::wstring& str) = 0;
	virtual OutputType getOutputType() const= 0;
	virtual ~BaseOutput() {};
};
