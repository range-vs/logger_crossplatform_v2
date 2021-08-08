#pragma once

#include <string>
#include <chrono>
#include <ctime>
#include <ctime>

class TimeUtils
{
	enum {SIZE_TIME_BUFFER = 512};
public:
	static std::string getCurrentTime()
	{
		std::time_t time(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
		char* timeStr = std::ctime(&time);
		return std::string(timeStr, timeStr + strlen(timeStr) - 1);
	}
	static std::wstring getCurrentTimeW()
	{
		std::time_t time(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
		char* timeStr = std::ctime(&time);
		return std::wstring(timeStr, timeStr + strlen(timeStr) - 1);
	}
};