#pragma once

#include "BaseOutput.h"
#include <fstream>

class HTMLFileOutput: public BaseOutput
{
	static std::string initStyles();
	static std::string initScript();

	std::string pathFile;
	std::ofstream file;
	std::string end_html;

	std::wstring pathFileW;
	std::wofstream fileW;
	std::wstring end_htmlW;

public:
	HTMLFileOutput() :file(), fileW() {};
	void setPathFile(const std::string& pf);
	void setPathFileW(const std::wstring& pf);
	void init(const std::string& nameGame, const std::string& versionGame) override;
	void init(const std::wstring& nameGame, const std::wstring& versionGame) override;
	void message(const LogType& lt, const std::string& str) override;
	void message(const LogType& lt, const std::wstring& str) override;
	OutputType getOutputType() const override;
	~HTMLFileOutput()override;
};

