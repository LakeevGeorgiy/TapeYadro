#include <gtest/gtest.h>
#include <filesystem>

#include "../src/data/services/CommandLineParser.h"

class CmdLineParserTests : public testing::Test {
public:

    std::string first_argument;
    std::shared_ptr<CommandLineParserInterface> parser_;

public:

    CmdLineParserTests(): first_argument("TapeYadro"), parser_(std::make_shared<CommandLineParser>()) {}
};

TEST_F(CmdLineParserTests, InputFileDefaultValue) {

    std::string input_file = "../files/input_file.txt";

    char* argv[] = {
        first_argument.data(),
    };
    auto files = parser_->ParseCommandLine(1, argv);
    EXPECT_EQ(input_file, files.input_file_path_);

}

TEST_F(CmdLineParserTests, OutputFileDefaultValue) {

    std::string output_file = "../files/output_file.txt";

    char* argv[] = {
        first_argument.data(),
    };
    auto files = parser_->ParseCommandLine(1, argv);
    EXPECT_EQ(output_file, files.output_file_path_);

}

TEST_F(CmdLineParserTests, EnvFileDefaultValue) {

    std::string env_file = "../files/.env";

    char* argv[] = {
        first_argument.data(),
    };
    auto files = parser_->ParseCommandLine(1, argv);
    EXPECT_EQ(env_file, files.env_file_path_);

}

TEST_F(CmdLineParserTests, InputFileShortFlag) {

    std::string flag = "-i";
    std::string input_file = "files/input.txt";
    std::string absolute_path = std::filesystem::absolute(input_file);

    char* argv[] = {
        first_argument.data(),
        flag.data(),
        input_file.data(),
    };
    auto files = parser_->ParseCommandLine(3, argv);
    EXPECT_EQ(absolute_path, files.input_file_path_);

}

TEST_F(CmdLineParserTests, InvalidInputFileShortFlag) {

    std::string flag = "-i";
    std::string input_file = "files/input2.txt";
    std::string absolute_path = std::filesystem::absolute(input_file);

    char* argv[] = {
        first_argument.data(),
        flag.data(),
        input_file.data(),
    };
    EXPECT_THROW(parser_->ParseCommandLine(3, argv), std::runtime_error);

}

TEST_F(CmdLineParserTests, InputFileLongFlag) {

    std::string flag = "--input-file";
    std::string input_file = "files/input.txt";
    std::string absolute_path = std::filesystem::absolute(input_file);

    char* argv[] = {
        first_argument.data(),
        flag.data(),
        input_file.data(),
    };
    auto files = parser_->ParseCommandLine(3, argv);
    EXPECT_EQ(absolute_path, files.input_file_path_);

}

TEST_F(CmdLineParserTests, InvalidInputFileLongFlag) {

    std::string flag = "--input-file";
    std::string input_file = "files/input2.txt";
    std::string absolute_path = std::filesystem::absolute(input_file);

    char* argv[] = {
        first_argument.data(),
        flag.data(),
        input_file.data(),
    };
    EXPECT_THROW(parser_->ParseCommandLine(3, argv), std::runtime_error);

}

TEST_F(CmdLineParserTests, OutputFileShortFlag) {

    std::string flag = "-o";
    std::string output_file = "files/output.txt";
    std::string absolute_path = std::filesystem::absolute(output_file);

    char* argv[] = {
        first_argument.data(),
        flag.data(),
        output_file.data(),
    };
    auto files = parser_->ParseCommandLine(3, argv);
    EXPECT_EQ(absolute_path, files.output_file_path_);

}

TEST_F(CmdLineParserTests, InvalidOutputFileShortFlag) {

    std::string flag = "-o";
    std::string output_file = "files/output2.txt";

    char* argv[] = {
        first_argument.data(),
        flag.data(),
        output_file.data(),
    };
    EXPECT_THROW(parser_->ParseCommandLine(3, argv), std::runtime_error);

}

TEST_F(CmdLineParserTests, OutputFileLongFlag) {

    std::string flag = "--output-file";
    std::string output_file = "files/output.txt";
    std::string absolute_path = std::filesystem::absolute(output_file);

    char* argv[] = {
        first_argument.data(),
        flag.data(),
        output_file.data(),
    };
    auto files = parser_->ParseCommandLine(3, argv);
    EXPECT_EQ(absolute_path, files.output_file_path_);

}

TEST_F(CmdLineParserTests, InvalidOutputFileLongFlag) {

    std::string flag = "--output-file";
    std::string output_file = "files/output2.txt";

    char* argv[] = {
        first_argument.data(),
        flag.data(),
        output_file.data(),
    };
    EXPECT_THROW(parser_->ParseCommandLine(3, argv), std::runtime_error);

}

TEST_F(CmdLineParserTests, EnvFileShortFlag) {

    std::string flag = "-e";
    std::string env_file = "files/.env";
    std::string absolute_path = std::filesystem::absolute(env_file);

    char* argv[] = {
        first_argument.data(),
        flag.data(),
        env_file.data(),
    };
    auto files = parser_->ParseCommandLine(3, argv);
    EXPECT_EQ(absolute_path, files.env_file_path_);

}

TEST_F(CmdLineParserTests, InvalidEnvFileShortFlag) {

    std::string flag = "-e";
    std::string env_file = "files/.env2";
    std::string absolute_path = std::filesystem::absolute(env_file);

    char* argv[] = {
        first_argument.data(),
        flag.data(),
        env_file.data(),
    };
    EXPECT_THROW(parser_->ParseCommandLine(3, argv), std::runtime_error);

}

TEST_F(CmdLineParserTests, EnvFileLongFlag) {

    std::string flag = "--env";
    std::string env_file = "files/.env";
    std::string absolute_path = std::filesystem::absolute(env_file);

    char* argv[] = {
        first_argument.data(),
        flag.data(),
        env_file.data(),
    };
    auto files = parser_->ParseCommandLine(3, argv);
    EXPECT_EQ(absolute_path, files.env_file_path_);

}

TEST_F(CmdLineParserTests, InvalidEnvFileLongFlag) {

    std::string flag = "--env";
    std::string env_file = "files/env2.txt";
    std::string absolute_path = std::filesystem::absolute(env_file);

    char* argv[] = {
        first_argument.data(),
        flag.data(),
        env_file.data(),
    };
    EXPECT_THROW(parser_->ParseCommandLine(3, argv), std::runtime_error);

}