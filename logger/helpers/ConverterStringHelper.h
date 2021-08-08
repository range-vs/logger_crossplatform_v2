#pragma once

class ConverterStringHelper
{
public:
	static float to_float(const std::wstring& str);

	static int to_int(const std::wstring& str);

	static int to_wchar_t(const std::wstring& str);

	static bool to_bool(const std::wstring& str);

	static float to_float(const char* str);

	static int to_int(const char* str);

	static int to_char(const char* str);

	static bool to_bool(const char* str);
	
	static std::wstring to_wstring(const char* str);

	static std::wstring to_wstring(const wchar_t* str);

	static std::wstring to_wstring(bool v);

	static std::wstring to_wstring(int v);

	static std::wstring to_wstring(float v);

	static std::vector<std::string> split(const std::string& s, char delim);

};