#include <string>
#include <cstdint>

class CommandLineParser {
public:

    struct NecessaryFiles {
        std::string input_file_path_;
        std::string output_file_path_;
        std::string env_file_path_;
        NecessaryFiles(
            std::string_view input_file_path,
            std::string_view output_file_path,
            std::string_view env_file_path 
        );

    };

private:

    constexpr static std::string_view kDefaultInputPath = "files/input_file.txt";
    constexpr static std::string_view kDefaultOutputPath = "files/output_file.txt";
    constexpr static std::string_view kDefaultEnvPath = ".env";

    constexpr static uint8_t kNumberOfFlags = 3;
    constexpr static uint8_t kNumberOfValues = 3;

    NecessaryFiles files_;

public:

    CommandLineParser();
    
    NecessaryFiles ParseCommandLine(int argc, char* argv[]);

private:

    bool IsValidPath(std::string_view path);
    void SetValue(std::string_view flag, std::string_view value);
};