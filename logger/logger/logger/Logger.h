#pragma once

#include "helpers/tuple_utils.h"
#include "helpers/time_utils.h"
#include "messages/TypeMessages.h"

#include "output/BaseOutput.h"
#include "helpers/StrConsts.h"

class Logger;
using LoggerPtr = std::shared_ptr<Logger>;

class Logger
{
	static LoggerPtr instance;

	bool _init;
	std::vector<std::shared_ptr<BaseOutput>> allOutputs;

	Logger();

	struct WriterParamsToBufferCallback
	{
		std::stringstream& buffer;
		std::string delimeter;

		WriterParamsToBufferCallback(std::stringstream& buffer, const std::string& del);

		template<std::size_t Index, class T>
		void operator()(T&& element);
	};

	struct WriterParamsToBufferCallbackW
	{
		std::wstringstream& buffer;
		std::wstring delimeter;

		WriterParamsToBufferCallbackW(std::wstringstream& buffer, const std::wstring& del);

		template<std::size_t Index, class T>
		void operator()(T&& element);
	};

protected:
	template<class ... Args>
	auto pack_to_tuple(Args... args);

	void release();

public:
	Logger(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(const Logger&) = delete;
	const Logger& operator=(Logger&&) = delete;
	static LoggerPtr getInstance();

	template<TypeOutput to, class ...Args>
	void printToLog(const LogType& id, Args... args);
	template<class ...Args>
	void init(const std::string& nameGame, const std::string& versionGame, Args... args);
	template<class ...Args>
	void init(const std::wstring& nameGame, const std::wstring& versionGame, Args... args);

	bool isInit()const noexcept;
	const std::vector<std::shared_ptr<BaseOutput>>& getAllOutputs()const;

	~Logger()
	{
		if(isInit())
			release();
	}
};


template<std::size_t Index, class T>
inline void Logger::WriterParamsToBufferCallback::operator()(T&& element)
{
	buffer << element << delimeter;
}

template<std::size_t Index, class T>
inline void Logger::WriterParamsToBufferCallbackW::operator()(T&& element)
{
	buffer << element << delimeter;
}

template<class ...Args>
inline auto Logger::pack_to_tuple(Args ...args)
{
	return std::make_tuple(std::forward<Args>(args)...);
}

template<TypeOutput to, class ...Args>
inline void Logger::printToLog(const LogType& id, Args... args)
{
	if constexpr(to == TypeOutput::IS_WSTRING)
	{
		assert(false && "wide char functional not implemented!");
	}
	else
	{
		std::stringstream buffer;
		buffer << "[" << TimeUtils::getCurrentTime() << "] ";
		TupleHelper::foreachTuple(WriterParamsToBufferCallback(buffer, " "), pack_to_tuple(args...));
		buffer << std::endl;
		for (auto&& output : allOutputs)
			output->message(id, buffer.str());
	}
}


template<class ...Args>
void Logger::init(const std::string& nameGame, const std::string& versionGame, Args... args)
{
	_init = true;
	std::initializer_list<std::shared_ptr<BaseOutput>> _argsInitializerList{ args... };

	for (auto&& output : _argsInitializerList)
	{
		output->init(nameGame, versionGame);
		allOutputs.emplace_back(output);
	}
}

template<class ...Args>
void Logger::init(const std::wstring& nameGame, const std::wstring& versionGame, Args... args)
{
	assert(false && "wide char functional not implemented!");
}