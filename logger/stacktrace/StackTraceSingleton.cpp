#include <pch.h>

#include "StackTraceSingleton.h"
#include "../stacktrace/StackTraceSingleton.h"

#ifdef _WIN32
void StackTraceSingleton::StackWalkerToString::OnOutput(LPCSTR szText)
{
	buffer += szText;
}

std::string StackTraceSingleton::StackWalkerToString::getStackTrace()
{
	std::string copy(buffer);
	buffer = "";
	return copy;
}

std::string StackTraceSingleton::getStacktraceForWindows(HANDLE hThread, const CONTEXT* context)
{
	sw.ShowCallstack(hThread, context);
	return "Stack trace: \n" + sw.getStackTrace();
}
#endif

std::unique_ptr<StackTraceSingleton> StackTraceSingleton::instance(nullptr);

std::unique_ptr<StackTraceSingleton>& StackTraceSingleton::getInstance()
{
	 if (!instance)
	 {
		 instance.reset(new StackTraceSingleton);
#ifdef _WIN32
		 instance->getStacktraceForWindows(); // first fake call
#endif
	 }
	return instance;
}

std::string StackTraceSingleton::getStacktrace
(
#ifdef _WIN32
	HANDLE hThread, const CONTEXT* context
#endif
)
{
	std::vector<std::string> lines;
	std::string out = "Stack trace: \n";
	int shiftStackTrace(0);
#ifdef _WIN32
	if(context)
		out.clear();
	lines = splitter("\n", getStacktraceForWindows(hThread, context));
	if(!context)
		shiftStackTrace = 4;
#elif __ANDROID__ 
	const size_t max = 30;
	void* buffer[max];
	std::ostringstream oss;
	swa.dumpBacktrace(oss, buffer, max);
	lines = splitter("\n", oss.str()); 
	shiftStackTrace = 3;
#elif __linux__ || __APPLE__
	lines = StackWalkerLinux::dumpBacktrace();
	shiftStackTrace = 2; 
#else
	return "Stack trace: no implemented!";
#endif
	out += std::accumulate(lines.begin() + shiftStackTrace, lines.end(), std::string{},
		[](std::string& start, const std::string& iter)
		{
			return start += iter + "\n";
		});
	return out;
}

std::vector<std::string> StackTraceSingleton::splitter(const std::string in_pattern, const std::string& content)
{
	std::vector<std::string> split_content;

	std::regex pattern(in_pattern);
	std::copy( std::sregex_token_iterator(content.cbegin(), content.cend(), pattern, -1),
			   std::sregex_token_iterator(),std::back_inserter(split_content));
	return split_content;
}
