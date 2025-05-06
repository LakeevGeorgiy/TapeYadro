#include <stdexcept>
#include <filesystem>
#include <iostream>

#include "CommandLineParser.h"

namespace fs = std::filesystem;

CommandLineParser::NecessaryFiles::NecessaryFiles(
    std::string_view input_file_path, 
    std::string_view output_file_path, 
    std::string_view env_file_path
)
    : input_file_path_(input_file_path)
    , output_file_path_(output_file_path)
    , env_file_path_(env_file_path)
{ }

CommandLineParser::CommandLineParser()
    : files_(kDefaultInputPath, kDefaultOutputPath, kDefaultEnvPath)
{ }

CommandLineParser::NecessaryFiles CommandLineParser::ParseCommandLine(int argc, char *argv[])
{

    if (argc > kNumberOfFlags + kNumberOfValues + 1) {
        throw std::invalid_argument("Too many arguments");
    }

    for (uint8_t i = 1; i < argc; ++i) {

        std::string_view arg = argv[i];
        if (arg[0] != '-') {
            continue;
        }

        if (i + 1 >= argc) {
            throw std::invalid_argument("Passing flag without value");
        }

        std::string_view value = argv[i + 1];
        SetValue(arg, value);
        ++i;

    }
    return files_;
}

bool CommandLineParser::IsValidPath(std::string_view path) {

    auto file_path = fs::absolute(path);

    if (fs::exists(file_path) && fs::is_regular_file(file_path)) {
        return true;
    }
    return false;
}

void CommandLineParser::SetValue(std::string_view flag, std::string_view value) {

    if (!IsValidPath(value)) {
        const std::string not_found_file = value.data();
        throw std::runtime_error("File doesn't exist: " + not_found_file);
    }

    if (flag == "-i" || flag == "--input-file") {
        files_.input_file_path_ = value;
    } else if (flag == "-o" || flag == "--output-file") {
        files_.output_file_path_ = value;
    } else if (flag == "-e" || flag == "--env") {
        files_.env_file_path_ = value;
    } else {
        const std::string unsupported_flag = flag.data();
        throw std::invalid_argument("This flag isn't support " + unsupported_flag);
    }
}