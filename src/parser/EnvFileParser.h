#pragma once

#include "../models/ConfigurationProperties.h"

class EnvFileParser {
private:

    ConfigurationProperties properties_;
    
public:

    EnvFileParser() = default;

    ConfigurationProperties ParseEnvFile(std::string_view path);

private:

    uint32_t GetNumberFromString(const std::string& line);
    void SetValue(std::string_view key, std::string_view value);
    std::string_view EraseWhitespaces(std::string_view line);
    void ParseLine(std::string_view line);
};