#include <fstream>
#include <iostream>
#include <regex>
#include <algorithm>
#include <filesystem>

#include "EnvFileParser.h"

namespace fs = std::filesystem;

ConfigurationProperties EnvFileParser::ParseEnvFile(std::string_view path) {
    auto file_path = fs::absolute(path);
    std::cout << "file env: " << file_path << "\n";
    std::ifstream in(file_path);
    if (!in.is_open()) {
        std::runtime_error("Can't read env file");
    }

    while (in.good()) {
        std::string line;
        std::getline(in, line);
        ParseLine(line);
    }
    if (!in.eof()) {
        throw std::runtime_error("Not all env file was read");
    }
    return properties_;
}

uint32_t EnvFileParser::GetNumberFromString(const std::string& line) {
    std::regex number_regex("^\\d+$");
    if (std::regex_match(line.data(), number_regex)) {
        return std::atoi(line.data());
    }
    throw std::invalid_argument("Not number in env file");
}

void EnvFileParser::SetValue(std::string_view key, std::string_view value) {

    std::string number_string(value);
    auto number = GetNumberFromString(number_string);
    std::cout << "number: " << number << "\n";

    if (key == "MEMORY_LIMIT") {
        properties_.memory_limit_ = number;
    } else if (key == "READ_LATENCY") {
        properties_.read_latency_ = number;
    } else if (key == "WRITE_LATENCY") {
        properties_.write_latency_ = number;
    } else if (key == "REWIND_LATENCY") {
        properties_.rewind_latency_ = number;
    } else if (key == "SHIFT_LATENCY") {
        properties_.shift_latency_ = number;
    } else {
        std::string not_supported_key(key);
        throw std::invalid_argument("This key isn't support in env file: " + not_supported_key);
    }
}

std::string_view EnvFileParser::EraseWhitespaces(std::string_view line) {

    auto pred = [](char symbol){
        return std::isspace(symbol);
    };

    auto start = std::find_if_not(line.begin(), line.end(), pred);
    
    auto end = std::min(
        std::find(start, line.end(), '#'),
        std::find_if(start, line.end(), pred)
    );

    return (start < end) ? std::string_view(start, end - start) : std::string_view();
}

void EnvFileParser::ParseLine(std::string_view line) {

    auto delimeter_index = line.find("=");
    if (delimeter_index >= line.size()) {
        throw new std::runtime_error("Env file is not correct");
    }

    auto key = line.substr(0, delimeter_index);
    auto value = line.substr(delimeter_index + 1);

    key = EraseWhitespaces(key);
    value = EraseWhitespaces(value);

    std::cout << "key: " << key << " value: " << value << "\n";
    SetValue(key, value);

}