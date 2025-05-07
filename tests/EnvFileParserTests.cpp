#include <gtest/gtest.h>
#include <filesystem>

#include "../src/data/services/EnvFileParser.h"

class EnvFileParserTests : public testing::Test {
public:

    std::shared_ptr<EnvFileParserInterface> parser_;

public:

    EnvFileParserTests(): parser_(std::make_shared<EnvFileParser>()) {}
};

TEST_F(EnvFileParserTests, FileNotExist) {
    
}