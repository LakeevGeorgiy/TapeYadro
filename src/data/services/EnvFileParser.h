#pragma once

#include "../../domain/services/EnvFileParserInterface.h"

class EnvFileParser : public EnvFileParserInterface {
private:

    ConfigurationProperties properties_;
    
public:

    EnvFileParser() = default;

    ConfigurationProperties ParseEnvFile(std::string_view path) override;

private:

    std::string GetAbsolutePath(std::string_view path);
    uint32_t GetNumberFromString(const std::string& line);
    void SetValue(std::string_view key, std::string_view value);
    std::string_view ErasePrefixWhitespaces(std::string_view line);
    std::string_view EraseWhitespaces(std::string_view line);
    void ParseLine(std::string_view line);
};