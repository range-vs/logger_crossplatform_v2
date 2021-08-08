#include <pch.h>
#include "LoggerParams.h"

void LoggerParams::setPathToFile(const std::string& path) noexcept
{
    this->pathToFile = path;
}

const std::string& LoggerParams::getPathToFile() const noexcept
{
    return this->pathToFile;
}
