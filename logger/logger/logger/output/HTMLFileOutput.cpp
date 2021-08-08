#include <pch.h>
#include "HTMLFileOutput.h"

#include "../helpers/time_utils.h"

#include "factory_messages/HTMLFactory.h"
#include "../../html/ctml.hpp"

std::string HTMLFileOutput::initStyles()
{
	/*
	Классы:
	row - строка таблицы базовый
	critical-error - строка таблицы критическая ошибка
	error - строка таблицы ошибка
	warning - строка таблицы предупреждение
	message - строка таблицы сообщение
	header - заголовок страницы
	panel-action - панель управления (чек боксы)
	table - таблица
	caption - заголовок таблицы
	*/
	return ".row{\
			  width: 100% ;\
			  font-size: 14pt;\
			  display: block;\
			  text-align: left\
			}\
			.caption{\
				text-align: left\
			}\
			.critical-error{\
			  background-color:red;\
			}\
			.error{\
			  background-color:orange;\
			}\
			.warning{\
			  background-color:yellow;\
			}\
			.message{\
			  background-color:green;\
			}\
			.header{\
			  text-align: center;\
			}\
			.panel-action{\
			  margin-left: 3% ;\
			}\
			.table{\
				width: 100%\
			}\
			.caption{\
			  font-size: 19pt\
			}";
}

std::string HTMLFileOutput::initScript()
{
	return "function panel_action(){\
				var buttons = ['critical-error', 'error', 'warning', 'message'];\
				var classes = ['.critical-error', '.error', '.warning', '.message'];\
					for (var i = 0; i < buttons.length; ++i) {\
						var elems = document.querySelectorAll(classes[i]);\
						var style = 'none';\
						if (document.getElementById(buttons[i]).checked) {\
							style = 'block';\
						}\
						for (var j = 0; j < elems.length; j++) {\
							elems[j].style.display = style;\
						}\
				}\
			}";
}

void HTMLFileOutput::setPathFile(const std::string& pf)
{
	pathFile = pf;
}

void HTMLFileOutput::setPathFileW(const std::wstring& pf)
{
	pathFileW = pf;
}

void HTMLFileOutput::init(const std::string& nameGame, const std::string& versionGame)
{
	file.open(pathFile);
	if(!file)
	{
		std::string error = strerror(errno);
        assert(file);
	}

	auto title("Log for session");
	CTML::Document log;
	log.html().SetAttribute("title", title);
	log.html().SetAttribute("lang", "en");
	log.head().AppendChild(CTML::Node("meta").SetAttribute("name", "viewport").SetAttribute("content", "width=device-width, initial-scale=1, shrink-to-fit=no"));
	log.head().AppendChild(CTML::Node("style", HTMLFileOutput::initStyles()));
	log.head().AppendChild(CTML::Node("script", HTMLFileOutput::initScript()));
	log.body().SetAttribute("class", "bg-light");

	// init common
	log.body().AppendChild(CTML::Node("h2").SetAttribute("class", "header"));
	// init leftBar
	log.body().AppendChild(CTML::Node("h3", "Time session: " + TimeUtils::getCurrentTime()));
	log.body().AppendChild(CTML::Node("h3", "Name project: " + nameGame));
	log.body().AppendChild(CTML::Node("h3", "Version project: " + versionGame));
	log.body().AppendChild(CTML::Node("br"));
	// инициализация панели управления
	log.body().AppendChild(CTML::Node("h3", "Control panel: ")).
		AppendChild(CTML::Node("input", "Critical errors:").SetAttribute("type", "checkbox").SetAttribute("checked", "").SetAttribute("id", "critical-error").SetAttribute("class", "panel-action").SetAttribute("onclick", "panel_action()")).
		AppendChild(CTML::Node("br")).
		AppendChild(CTML::Node("input", "Errors:").SetAttribute("type", "checkbox").SetAttribute("checked", "").SetAttribute("id", "error").SetAttribute("class", "panel-action").SetAttribute("onclick", "panel_action()")).
		AppendChild(CTML::Node("br")).
		AppendChild(CTML::Node("input", "Warnings:").SetAttribute("type", "checkbox").SetAttribute("checked", "").SetAttribute("id", "warning").SetAttribute("class", "panel-action").SetAttribute("onclick", "panel_action()")).
		AppendChild(CTML::Node("br")).
		AppendChild(CTML::Node("input", "Messages:").SetAttribute("type", "checkbox").SetAttribute("checked", "").SetAttribute("id", "message").SetAttribute("class", "panel-action").SetAttribute("onclick", "panel_action()")).
		AppendChild(CTML::Node("br"));

	// инит таблицы
	log.body().AppendChild(CTML::Node("table").SetAttribute("class", "table").AppendChild(CTML::Node("caption", "Log").SetAttribute("class", "caption")));

	// получение окончания файла (для перезаписи)
	std::string text(log.ToString());
	size_t index(0);
	std::string signReplaced("&lt;");
	std::string signReplace("<");
	while (true) // заменяем 
	{
		index = text.find(signReplaced, index);
		if (index == std::string::npos)
			break;
		text.replace(index, signReplaced.length(), signReplace);
		index+= signReplaced.length();
	}
	// find END_HTML
	index = text.find("</table>");
	assert(index != std::string::npos && "Error find end block in html - code");
	end_html = std::regex_replace(text.substr(index), std::regex("([\\s]*)"), "");
	text.resize(index);
	text += end_html;

	// запись в файл
	file << text;
	assert(file && "Error write html - file from logger!");
	file.flush();
}

void HTMLFileOutput::init(const std::wstring& nameGame, const std::wstring& versionGame)
{
	assert(false && "wide char functional not implemented!");
}

void HTMLFileOutput::message(const LogType& lt, const std::string & str)
{
	auto messageBuilder(CreatorMessagesHTMLFileOutput::create(lt));
	file.seekp(-static_cast<int>(sizeof(char) * (end_html.length())), std::ios::cur);
	assert(file && "Error write html - file from logger!");
	file << messageBuilder->createTableLine(str) << end_html;
	assert(file && "Error write html - file from logger!");
	file.flush();
}

void HTMLFileOutput::message(const LogType& lt, const std::wstring& str)
{
	assert(false && "wide char functional not implemented!");
}

OutputType HTMLFileOutput::getOutputType() const
{
	return OutputType::HTML_FILE;
}

HTMLFileOutput::~HTMLFileOutput()
{

}

