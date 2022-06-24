#include <pch.h>
#include "Logger.h"

LoggerPtr Logger::instance(nullptr);

Logger::Logger()
:_init(false)
{
}

LoggerPtr Logger::getInstance()
{
	if (!instance)
	{
		instance.reset(new Logger);
		assert(instance);
	}
	return instance;
}

void Logger::release()
{
	
}

bool Logger::isInit()const noexcept
{
	return _init;
}

const std::vector<std::shared_ptr<BaseOutput>>& Logger::getAllOutputs()const
{
	return allOutputs;
}


Logger::WriterParamsToBufferCallback::WriterParamsToBufferCallback(std::stringstream & buffer, const std::string& del)
: buffer(buffer),
delimeter(del)
{
}

Logger::WriterParamsToBufferCallbackW::WriterParamsToBufferCallbackW(std::wstringstream& buffer, const std::wstring& del)
: buffer(buffer),
delimeter(del)
{
}
