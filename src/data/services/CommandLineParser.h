#pragma once

#include <string>
#include <cstdint>

#include "../../domain/services/CommandLineParserInterface.h"

class CommandLineParser : public CommandLineParserInterface {
private:

    constexpr static uint8_t kNumberOfFlags = 3;
    constexpr static uint8_t kNumberOfValues = 3;

    NecessaryFiles files_;

public:

    CommandLineParser();
    
    NecessaryFiles ParseCommandLine(int argc, char* argv[]) override;

private:

    std::string GetAbsolutePath(std::string_view path);
    bool IsValidPath(std::string_view path);
    void SetValue(std::string_view flag, std::string_view value);
};