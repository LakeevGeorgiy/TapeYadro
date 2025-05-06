#pragma once

#include <cstdint>
#include <string>

class ConfigurationProperties {
private:

    uint32_t memory_limit_;
    uint32_t read_latency_;
    uint32_t write_latency_;
    uint32_t rewind_latency_;
    uint32_t shift_latency_;
    std::string input_file_;
    std::string output_file_;

public:

    ConfigurationProperties(std::string_view input_file, std::string_view output_file);

    void ParseEnvFile(std::string_view path);

private:

    uint32_t GetNumberFromString(const std::string& line);
    void SetValue(std::string_view key, std::string_view value);
    std::string_view EraseWhitespaces(std::string_view line);
    void ParseLine(std::string_view line);
    

};