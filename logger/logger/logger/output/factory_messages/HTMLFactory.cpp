#include "pch.h"

#include "HTMLFactory.h"

#include "../../messages/TypeMessages.h"
#include "../../../../helpers/ConverterStringHelper.h"
#include "../../../../helpers/StatusFunction.h"
#include "../../../html/ctml.hpp"

#ifdef _WIN32
#include "logger/logger/helpers/WindowsFormatMessage.h"
#endif

std::string MessageHTMLFileOutput::createTableLine(const std::string& msg)
{
	auto arrayStrings(ConverterStringHelper::split(msg, '\n'));
	CTML::Node row("tr");
	row.SetAttribute("class", "row message");
	CTML::Node th("th");
	for (auto&& as : arrayStrings)
		th.AppendChild(CTML::Node("p", as));
	row.AppendChild(th);
	return row.ToString();
}

std::string WarningHTMLFileOutput::createTableLine(const std::string& msg)
{
	auto arrayStrings(ConverterStringHelper::split(msg, '\n'));
	CTML::Node row("tr");
	row.SetAttribute("class", "row warning");
	CTML::Node th("th");
	for (auto&& as : arrayStrings)
		th.AppendChild(CTML::Node("p", as));
	row.AppendChild(th);
	return row.ToString();
}

std::string ErrorHTMLFileOutput::createTableLine(const std::string& msg)
{
	auto arrayStrings(ConverterStringHelper::split(msg, '\n'));
	CTML::Node row("tr");
	row.SetAttribute("class", "row error");
	CTML::Node th("th");
	for (auto&& as : arrayStrings)
		th.AppendChild(CTML::Node("p", as));
	row.AppendChild(th);
	return row.ToString();
}

std::string CriticalErrorHTMLFileOutput::createTableLine(const std::string& msg)
{
	auto arrayStrings(ConverterStringHelper::split(msg, '\n'));
	CTML::Node row("tr");
	row.SetAttribute("class", "row critical-error");
	CTML::Node th("th");
	for (auto&& as : arrayStrings)
		th.AppendChild(CTML::Node("p", as));
#ifdef _WIN32
	th.AppendChild(CTML::Node("p", "\nGetLastError WinAPI: " + WindowsFormatMessage::GetErrorMessage(GetLastError())));
#endif
	row.AppendChild(th);
	return row.ToString();
}

std::map<LogType, std::shared_ptr<BaseMessageHTMLFileOutput>> CreatorMessagesHTMLFileOutput::messageCreators
(
	{
		{LogType::LOG_MESSAGE, std::make_shared<MessageHTMLFileOutput>()},
		{LogType::LOG_ERROR, std::make_shared<ErrorHTMLFileOutput>()},
		{LogType::LOG_WARNING, std::make_shared<WarningHTMLFileOutput>()},
		{LogType::LOG_CRITICAL_ERROR, std::make_shared<CriticalErrorHTMLFileOutput>()}
	}
);

std::shared_ptr<BaseMessageHTMLFileOutput>& CreatorMessagesHTMLFileOutput::create(const LogType & lt)
{
	checkCriticalError(messageCreators.find(lt) == messageCreators.end(), "Error: factory CreatorMessagesHTMLFileOutput not found a class!");
	return messageCreators[lt]; 
}