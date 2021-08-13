#pragma once

#include "Logger.h"

#include "output/HTMLFileOutput.h"
#include "output/TerminalOutput.h"
#ifdef _WIN32
#include "output/VisualStudioOutput.h"
#include "output/WinAPIOutput.h"
#elif __ANDROID__
#include "output/AndroidLogcatOutput.h"
#include "output/AndroidToastOutput.h"
#elif __APPLE__
#include "output/AppleTerminalOutput.h"
#include "output/MacOutput.h"
#endif

#include <string>

/*
Использование: 
Сначала инициализировать логгер методом log_init, и передать в него имя приложения,его версию (можно и пустые строки кинуть).
Далее вызывать один из четырёх методов, в зависимости от логирования:
- log_debug - сообщение;
- log_error - ошибка;
- log_critical_error - критическая ошибка с завершением приложения;
- log_warning - предупреждение.
и передать любое количество аргументов в функцию. Аргументы разделяются пробелом, и для вывода
должны перегружать operator<< (ostream).
Каждый метод возвращает false, если логгер не инициализирован, или true, если логгер готов к работе.
*/

#ifndef NDEBUG

class log
{
public:
	template<class ...Args>
	static void init(const std::string& nameGame, const std::string& versionGame, Args... args);

	template<class ...Args>
	static void initw(const std::wstring& nameGame, const std::wstring& versionGame, Args... args);
	
	template<TypeOutput to, class ...Args >
	static bool debug(Args... args);

	template<TypeOutput to, class ...Args >
	static bool error(Args... args);

	template<TypeOutput to, class ...Args >
	static bool critical_error(Args... args);

	template<TypeOutput to, class ...Args >
	static bool warning(Args... args);
};

template<class ...Args>
void log::init(const std::string& nameGame, const std::string& versionGame, Args... args)
{
	Logger::getInstance()->init(nameGame, versionGame, args...);
}

template<class ...Args>
void log::initw(const std::wstring& nameGame, const std::wstring& versionGame, Args ...args)
{
	Logger::getInstance()->init(nameGame, versionGame, args...);
}

template<TypeOutput to, class ...Args>
bool log::debug(Args... args)
{
	if (!Logger::getInstance()->isInit())
		return false;
	Logger::getInstance()->printToLog<to>(LogType::LOG_MESSAGE, args...);
	return true;
}

template<TypeOutput to, class ...Args>
bool log::error(Args... args)
{
	if (!Logger::getInstance()->isInit())
		return false;
	Logger::getInstance()->printToLog<to>(LogType::LOG_ERROR, args...);
	return true;
}

template<TypeOutput to, class ...Args>
bool log::critical_error(Args... args)
{
	if (!Logger::getInstance()->isInit())
		return false;
	Logger::getInstance()->printToLog<to>(LogType::LOG_CRITICAL_ERROR, args...);
	return true;
}

template<TypeOutput to, class ...Args>
bool log::warning(Args... args)
{
	if (!Logger::getInstance()->isInit())
		return false;
	Logger::getInstance()->printToLog<to>(LogType::LOG_WARNING, args...);
	return true;
}

#define log_init(name, version, ...) log::init(name, version, __VA_ARGS__)
#define log_debug(...) log::debug<TypeOutput::IS_STRING>(std::string("File: ") + __FILE__, std::string(", function: ") + __func__, ", line: " + std::to_string(__LINE__), ". Message: ", __VA_ARGS__)
#define log_error(...) log::error<TypeOutput::IS_STRING>(std::string("File: ") + __FILE__, std::string(", function: ") + __func__, ", line: " + std::to_string(__LINE__), ". Message: ", __VA_ARGS__)
#define log_critical_error(...) log::critical_error<TypeOutput::IS_STRING>(std::string("File: ") + __FILE__, std::string(", function: ") + __func__, ", line: " + std::to_string(__LINE__), ". Message: ", __VA_ARGS__)
#define log_warning(...) log::warning<TypeOutput::IS_STRING>(std::string("File: ") + __FILE__, std::string(", function: ") + __func__, ", line: " + std::to_string(__LINE__), ". Message: ", __VA_ARGS__)

#else
class log
{
public:
	template<TypeOutput to, class ...Args >
	static void init(const std::string& nameGame, const std::string& versionGame, Args... args){}

	template<TypeOutput to, class ...Args>
	static void initW(const std::string& nameGame, const std::string& versionGame, Args... args){}

	template<TypeOutput to, class ...Args >
	static bool debug(Args... args) { return true; }

	template<TypeOutput to, class ...Args >
	static bool error(Args... args) { return true; }

	template<TypeOutput to, class ...Args >
	static bool critical_error(Args... args) { return true; }

	template<TypeOutput to, class ...Args >
	static bool warning(Args... args) { return true; }
};

#define log_init(name, version, ...)
#define log_debug(...) 
#define log_error(...) 
#define log_critical_error(...) 
#define log_warning(...) 

#endif
