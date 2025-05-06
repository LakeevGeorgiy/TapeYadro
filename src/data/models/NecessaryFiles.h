#pragma once

#include <string>

class NecessaryFiles {
public:

    std::string input_file_path_;
    std::string output_file_path_;
    std::string env_file_path_;

    constexpr static std::string_view kDefaultInputPath = "../files/input_file.txt";
    constexpr static std::string_view kDefaultOutputPath = "../files/output_file.txt";
    constexpr static std::string_view kDefaultEnvPath = "../files/.env";

public:

    NecessaryFiles();
    NecessaryFiles(
        std::string_view input_file_path,
        std::string_view output_file_path,
        std::string_view env_file_path 
    );

};