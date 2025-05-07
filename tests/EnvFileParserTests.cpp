#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

#include "../src/data/services/EnvFileParser.h"

class EnvFileParserTests : public testing::Test {
public:

    std::string env_file_;
    std::shared_ptr<EnvFileParserInterface> parser_;

public:

    EnvFileParserTests(): env_file_("files/.env"), parser_(std::make_shared<EnvFileParser>()) {}

    void WriteEnvFile(std::string_view file);
};

void EnvFileParserTests::WriteEnvFile(std::string_view file) {
    auto env = std::filesystem::absolute(env_file_);
    std::ofstream out(env);
    if (!out.is_open()) {
        throw std::runtime_error("Can't open env file for test");
    }

    out << file;
}


TEST_F(EnvFileParserTests, FileNotExist) {
    std::string flag = "-i";
    std::string env_file = "files/.env2";
    std::string absolute_path = std::filesystem::absolute(env_file);

    EXPECT_THROW(parser_->ParseEnvFile(env_file), std::runtime_error);
}

TEST_F(EnvFileParserTests, SimpleMemoryLimit) {
    
    const std::string file = { R"( MEMORY_LIMIT=100 )"};

    WriteEnvFile(file);

    auto properties = parser_->ParseEnvFile(env_file_);
    EXPECT_EQ(properties.memory_limit_, 100);
}

TEST_F(EnvFileParserTests, SimpleReadLatency) {
    
    const std::string file = { R"( READ_LATENCY=1 )"};

    WriteEnvFile(file);

    auto properties = parser_->ParseEnvFile(env_file_);
    EXPECT_EQ(properties.read_latency_, 1);
}

TEST_F(EnvFileParserTests, SimpleWriteLatency) {
    
    const std::string file = { R"( WRITE_LATENCY=10 )"};

    WriteEnvFile(file);

    auto properties = parser_->ParseEnvFile(env_file_);
    EXPECT_EQ(properties.write_latency_, 10);
}

TEST_F(EnvFileParserTests, SimpleRewindLatency) {
    
    const std::string file = { R"( REWIND_LATENCY=100 )"};

    WriteEnvFile(file);

    auto properties = parser_->ParseEnvFile(env_file_);
    EXPECT_EQ(properties.rewind_latency_, 100);
}

TEST_F(EnvFileParserTests, SimpleShiftLatency) {
    
    const std::string file = { R"( SHIFT_LATENCY=5 )"};

    WriteEnvFile(file);

    auto properties = parser_->ParseEnvFile(env_file_);
    EXPECT_EQ(properties.shift_latency_, 5);
}

TEST_F(EnvFileParserTests, SeveralConfigLine) {
    
    const std::string file = { R"( MEMORY_LIMIT=100
        SHIFT_LATENCY=7 )"};

    WriteEnvFile(file);

    auto properties = parser_->ParseEnvFile(env_file_);
    EXPECT_EQ(properties.memory_limit_, 100);
    EXPECT_EQ(properties.shift_latency_, 7);
}

TEST_F(EnvFileParserTests, UsingCommentsInFile) {
    
    const std::string file = { R"( MEMORY_LIMIT=100 # some comment )"};

    WriteEnvFile(file);

    auto properties = parser_->ParseEnvFile(env_file_);
    EXPECT_EQ(properties.memory_limit_, 100);
}

TEST_F(EnvFileParserTests, LineIsComment) {
    
    const std::string file = { R"( # some comment 
        MEMORY_LIMIT=100)"};

    WriteEnvFile(file);

    auto properties = parser_->ParseEnvFile(env_file_);
    EXPECT_EQ(properties.memory_limit_, 100);
}

TEST_F(EnvFileParserTests, EmptyLine) {
    
    const std::string file = { R"( 
        # some comment 
        MEMORY_LIMIT=100
    )"};

    WriteEnvFile(file);

    auto properties = parser_->ParseEnvFile(env_file_);
    EXPECT_EQ(properties.memory_limit_, 100);
}

TEST_F(EnvFileParserTests, AllConfiguration) {
    
    const std::string file = { R"( 
        # some comment 
        MEMORY_LIMIT=100
        READ_LATENCY=8
        WRITE_LATENCY=7
        REWIND_LATENCY=9
        SHIFT_LATENCY=10
    )"};

    WriteEnvFile(file);

    auto properties = parser_->ParseEnvFile(env_file_);
    EXPECT_EQ(properties.memory_limit_, 100);
    EXPECT_EQ(properties.read_latency_, 8);
    EXPECT_EQ(properties.write_latency_, 7);
    EXPECT_EQ(properties.rewind_latency_, 9);
    EXPECT_EQ(properties.shift_latency_, 10);
}

TEST_F(EnvFileParserTests, NotSupportKey) {
    
    const std::string file = { R"( 
        # some comment 
        MEMORY_LIMI=100
    )"};

    WriteEnvFile(file);

    EXPECT_THROW(parser_->ParseEnvFile(env_file_), std::invalid_argument);
}

TEST_F(EnvFileParserTests, NotNumberAsValue) {
    
    const std::string file = { R"( 
        # some comment 
        MEMORY_LIMIT=1f
    )"};

    WriteEnvFile(file);

    EXPECT_THROW(parser_->ParseEnvFile(env_file_), std::invalid_argument);
}

TEST_F(EnvFileParserTests, NotCorrectForm) {
    
    const std::string file = { R"( 
        # some comment 
        MEMORY_LIMIT = 1f
    )"};

    WriteEnvFile(file);

    EXPECT_THROW(parser_->ParseEnvFile(env_file_), std::invalid_argument);
}

TEST_F(EnvFileParserTests, TooLongNumber) {
    
    const std::string file = { R"( 
        # some comment 
        MEMORY_LIMIT=100000000000000
    )"};

    WriteEnvFile(file);

    EXPECT_THROW(parser_->ParseEnvFile(env_file_), std::invalid_argument);
}

TEST_F(EnvFileParserTests, IllFormedEnvFile) {
    
    const std::string file = { R"( 
        # some comment 
        MEMORY_LIMIT: 100000000000000
    )"};

    WriteEnvFile(file);

    EXPECT_ANY_THROW(parser_->ParseEnvFile(env_file_));
}