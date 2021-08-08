#pragma once

class LoggerParams
{
    std::string pathToFile;
public:
    void setPathToFile(const std::string& path) noexcept;
    const std::string& getPathToFile()const noexcept;

};


