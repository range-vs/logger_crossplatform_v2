#pragma once

#ifdef __APPLE__

#include "BaseOutput.h"

class AppleTerminalOutput : public BaseOutput
{

public:
	void init(const std::string& nameGame, const std::string& versionGame) override;
	void init(const std::wstring& nameGame, const std::wstring& versionGame) override;
	void message(const LogType& lt, const std::string& str) override;
	void message(const LogType& lt, const std::wstring& str) override;
	OutputType getOutputType()const override;
	~AppleTerminalOutput()override;
};
#endif
