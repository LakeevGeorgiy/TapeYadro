#include "NecessaryFiles.h"

NecessaryFiles::NecessaryFiles()
    : input_file_path_(kDefaultInputPath)
    , output_file_path_(kDefaultOutputPath)
    , env_file_path_(kDefaultEnvPath)
{ }

NecessaryFiles::NecessaryFiles(
    std::string_view input_file_path,
    std::string_view output_file_path,
    std::string_view env_file_path)
    : input_file_path_(input_file_path), output_file_path_(output_file_path), env_file_path_(env_file_path)
{ }
