#pragma once

#include "BaseOutput.h"

class TerminalOutput: public BaseOutput
{

public:
	void init(const std::string& nameGame, const std::string& versionGame) override;
	void init(const std::wstring& nameGame, const std::wstring& versionGame) override;
	void message(const LogType& lt, const std::string& str) override;
	void message(const LogType& lt, const std::wstring& str) override;
	OutputType getOutputType() const override;
	~TerminalOutput()override;
};

