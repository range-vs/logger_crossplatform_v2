#include <pch.h>

#include "StatusFunction.h"

namespace stat_func
{
    bool checkExpression(bool expression)
    {
        return expression;
    }
#ifdef WIN32
    bool checkExpression(HRESULT expression)
    {
        return FAILED(expression);
    }
#endif
}

namespace init_logger
{
    #ifdef _WIN32
    void _logger_init(const std::string& path)
    {
        std::shared_ptr<VisualStudioOutput> visualStudioOutput(std::make_shared<VisualStudioOutput>()); 
        std::shared_ptr<WinAPIOutput> winApiOutput(std::make_shared<WinAPIOutput>()); 
        std::shared_ptr<HTMLFileOutput> htmlFileOutput(std::make_shared<HTMLFileOutput>()); 
        htmlFileOutput->setPathFile(path); 
        std::shared_ptr<TerminalOutput> terminalOutput(std::make_shared<TerminalOutput>()); 
        log_init("alien engine", "0.0.1", htmlFileOutput, terminalOutput, visualStudioOutput, winApiOutput); 
    }
    #elif __ANDROID__ 
    void _logger_init(JNIEnv* env, jobject activity, const std::string& path)
    {
        std::shared_ptr<HTMLFileOutput> htmlFileOutput(std::make_shared<HTMLFileOutput>());
        htmlFileOutput->setPathFile(path);
        std::shared_ptr<AndroidLogcatOutput> androidLogcatOutput(std::make_shared<AndroidLogcatOutput>()); 
        std::shared_ptr<TerminalOutput> terminalOutput(std::make_shared<TerminalOutput>());
        log_init("alien engine", "0.0.1", htmlFileOutput, terminalOutput, androidLogcatOutput);
    }
    #elif __linux__
    void _logger_init(const std::string& path)
    {
        std::shared_ptr<HTMLFileOutput> htmlFileOutput(std::make_shared<HTMLFileOutput>());
        htmlFileOutput->setPathFile(path);
        std::shared_ptr<TerminalOutput> terminalOutput(std::make_shared<TerminalOutput>());
        log_init("alien engine", "0.0.1", htmlFileOutput, terminalOutput);
    }
    #elif __APPLE__
    void _logger_init(const std::string& path)
    {
        std::shared_ptr<HTMLFileOutput> htmlFileOutput(std::make_shared<HTMLFileOutput>());
        htmlFileOutput->setPathFile(path);
        std::shared_ptr<AppleTerminalOutput> terminalOutput(std::make_shared<AppleTerminalOutput>());
        std::shared_ptr<MacOutput> macOutput(std::make_shared<MacOutput>());
        log_init("alien engine", "0.0.1", htmlFileOutput, terminalOutput, macOutput);
    }
    #endif
}
