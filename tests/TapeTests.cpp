#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

#include "../src/data/services/EnvFileParser.h"
#include "../src/data/services/Tape.h"

class TapeTests : public testing::Test {
public:

    std::string input_file_;
    std::string output_file_;
    std::string env_file_;
    std::shared_ptr<TapeInterface> tape_;

public:

    TapeTests() {
        input_file_ = std::filesystem::absolute("files/input.txt");
        output_file_ = std::filesystem::absolute("files/output.txt");
        env_file_ = std::filesystem::absolute("files/.env");

        auto env_parser = std::make_shared<EnvFileParser>();
        tape_ = std::make_shared<Tape>(env_parser);

        const std::string file = { R"(
            MEMORY_LIMIT=8
        )"};
        SetUp(file);
    }

    void SetUp(std::string_view file);
    void WriteFile(std::string_view file);
    std::vector<uint32_t> ReadFile();

};

void TapeTests::SetUp(std::string_view file) {

    std::ofstream out(env_file_);
    out << file;
    out.close();

    tape_->SetUpTape("files/.env");
}

void TapeTests::WriteFile(std::string_view file) {
    std::ofstream out(input_file_);
    out << file;
    out.close();
}

std::vector<uint32_t> TapeTests::ReadFile() {
    
    std::vector<uint32_t> values;
    std::ifstream in(output_file_);

    while (in.good()) {
        uint32_t value;
        in >> value;
        values.emplace_back(value);
    }
    in.close();
    return values;
}

TEST_F(TapeTests, SimpleSortedTest) {
    const std::string file = { R"(
        1 2 3 4 5 
    )"};

    WriteFile(file);
    tape_->SortFile(input_file_, output_file_);

    const auto result = ReadFile();
    EXPECT_TRUE(std::is_sorted(result.begin(), result.end()));
}

TEST_F(TapeTests, SimpleSortedTestNewline) {
    const std::string file = { R"(
        1
        2
        3
        4
        5
    )"};

    WriteFile(file);
    tape_->SortFile(input_file_, output_file_);

    const auto result = ReadFile();
    EXPECT_TRUE(std::is_sorted(result.begin(), result.end()));
}

TEST_F(TapeTests, SimpleSortedWithEmptyLinesTest) {
    const std::string file = { R"(
        1
        2

        3

        4


        5
    )"};

    WriteFile(file);
    tape_->SortFile(input_file_, output_file_);

    const auto result = ReadFile();
    EXPECT_TRUE(std::is_sorted(result.begin(), result.end()));
}

TEST_F(TapeTests, SortedDescentTest) {
    const std::string file = { R"(
        5 4 3 2 1
    )"};

    WriteFile(file);
    tape_->SortFile(input_file_, output_file_);

    const auto result = ReadFile();
    EXPECT_TRUE(std::is_sorted(result.begin(), result.end()));
}

TEST_F(TapeTests, ShuffleValueTest) {
    const std::string file = { R"(
        5 4 3 9 3 0 4 1 3
    )"};

    WriteFile(file);
    tape_->SortFile(input_file_, output_file_);

    const auto result = ReadFile();
    EXPECT_TRUE(std::is_sorted(result.begin(), result.end()));
}

TEST_F(TapeTests, EqualValuesTest) {
    const std::string file = { R"(
        1 1 1 1 1 1 
    )"};

    WriteFile(file);
    tape_->SortFile(input_file_, output_file_);

    const auto result = ReadFile();
    EXPECT_TRUE(std::is_sorted(result.begin(), result.end()));
}

TEST_F(TapeTests, CountNumberOfBatches) {
    const std::string file = { R"(
        1 1 1 1 1 1 
    )"};

    WriteFile(file);
    tape_->SortFile(input_file_, output_file_);

    const auto result = ReadFile();
    EXPECT_TRUE(std::is_sorted(result.begin(), result.end()));
}