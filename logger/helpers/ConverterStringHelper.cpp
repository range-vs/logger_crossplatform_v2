#include <pch.h>

#include "ConverterStringHelper.h"
#include "StatusFunction.h"

float ConverterStringHelper::to_float(const std::wstring& str)
{
	float _out;
	std::wstringstream _to_double;
	_to_double << str;
	_to_double >> _out;
	checkCriticalError(!_to_double, "Error converter wstring: to float");
	return _out;
}

int ConverterStringHelper::to_int(const std::wstring& str)
{
	int _out;
	std::wstringstream _to_int;
	_to_int << str;
	_to_int >> _out;
	checkCriticalError(!_to_int, "Error converter wstring: to int");
	return _out;
}

int ConverterStringHelper::to_wchar_t(const std::wstring& str)
{
	return static_cast<wchar_t>(to_int(str));
}

bool ConverterStringHelper::to_bool(const std::wstring& str)
{
	bool _out;
	std::wstringstream _to_bool;
	_to_bool << str;
	_to_bool >> _out;
	checkCriticalError(!_to_bool, "Error converter wstring: to bool");
	return _out;
}

float ConverterStringHelper::to_float(const char* str)
{
	float _out;
	std::stringstream _to_double;
	_to_double << str;
	_to_double >> _out;
	checkCriticalError(!_to_double, "Error converter const char* to float");
	return _out;
}

int ConverterStringHelper::to_int(const char* str)
{
	int _out;
	std::stringstream _to_int;
	_to_int << str;
	_to_int >> _out;
	checkCriticalError(!_to_int, "Error converter const char*: to float");
	return _out;
}

int ConverterStringHelper::to_char(const char* str)
{
	return static_cast<char>(to_int(str));
}

bool ConverterStringHelper::to_bool(const char* str)
{
	bool _out;
	std::stringstream _to_bool;
	_to_bool << str;
	_to_bool >> _out;
	checkCriticalError(!_to_bool, "Error converter const char*: to bool");
	return _out;
}

std::wstring ConverterStringHelper::to_wstring(const char* str)
{
	std::wstring _out;
	std::wstringstream _to_wstring;
	_to_wstring << str;
	_to_wstring >> _out;
	checkCriticalError(!_to_wstring, "Error converter const char*: to wstring");
	return _out;
}

std::wstring ConverterStringHelper::to_wstring(const wchar_t* str)
{
	std::wstring _out;
	std::wstringstream _to_wstring;
	_to_wstring << str;
	_to_wstring >> _out;
	checkCriticalError(!_to_wstring, "Error converter const wchar_t*: to wstring");
	return _out;
}

std::wstring ConverterStringHelper::to_wstring(bool v)
{
	std::wstring _out;
	std::wstringstream _to_wstring;
	_to_wstring << v;
	_to_wstring >> _out;
	checkCriticalError(!_to_wstring, "Error converter float to wstring");
	return _out;
}

std::wstring ConverterStringHelper::to_wstring(int v)
{
	std::wstring _out;
	std::wstringstream _to_wstring;
	_to_wstring << v;
	_to_wstring >> _out;
	checkCriticalError(!_to_wstring, "Error converter int to wstring");
	return _out;
}

std::wstring ConverterStringHelper::to_wstring(float v)
{
	std::wstring _out;
	std::wstringstream _to_wstring;
	_to_wstring << v;
	_to_wstring >> _out;
	checkCriticalError(!_to_wstring, "Error converter float to wstring");
	return _out;
}

std::vector<std::string> ConverterStringHelper::split(const std::string& s, char delim)
{
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) 
		if (item.length() > 0) 
			elems.push_back(item);
	return elems;
}
