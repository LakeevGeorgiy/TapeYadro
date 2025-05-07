#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <filesystem>
#include <iostream>

#include "Tape.h"

namespace fs = std::filesystem;

Tape::Tape(std::shared_ptr<EnvFileParserInterface> parser): cnt_batch_(0), parser_(parser), properties_() { }

void Tape::SetUpTape(std::string_view env_file) {
    properties_ = parser_->ParseEnvFile(env_file);
}

void Tape::SortFile(std::string_view input_file, std::string_view output_file) {
    CreateBatchesFromInput(input_file);
    MergeBatches(output_file);
    ClearTempDirectory();
}

std::string Tape::GetAbsolutePath(std::string_view path) {
    return fs::absolute(path);
}

void Tape::CreateBatchesFromInput(std::string_view input_file) {

    auto absolute_path = GetAbsolutePath(input_file);
    std::ifstream in(absolute_path);
    if (!in.is_open()) {
        std::runtime_error("Can't read input file");
    }

    size_t batch_size = properties_.memory_limit_ / sizeof(uint32_t);
    std::vector<uint32_t> values(batch_size);
    values.shrink_to_fit();

    while (in.good()) {
        size_t i = 0;
        for ( ; i < batch_size && in.good(); ++i) {
            uint32_t value;
            in >> value;
            values[i] = value;
        }
        SortAndSaveBatch(values, i);
        ++cnt_batch_;
    }
    if (!in.eof()) {
        throw std::runtime_error("Not all input file was read");
    }
    in.close();
}

void Tape::SortAndSaveBatch(std::vector<uint32_t> &batch_values, size_t batch_size)
{
    std::sort(batch_values.begin(), batch_values.begin() + batch_size);

    std::string batch_file("tmp/batch" + std::to_string(cnt_batch_) + ".txt");
    auto batch_path = GetAbsolutePath(batch_file);

    std::ofstream out(batch_path);

    if (!out.is_open()) {
        std::runtime_error("Can't create and write to temporary file");
    }

    for (size_t i = 0; i < batch_size; ++i) {
        out << batch_values[i] << " ";
    }
    out.close();
}

void Tape::MergeBatches(std::string_view output_file) {

    std::vector<std::ifstream> batch_streams;
    std::priority_queue<
        std::pair<uint32_t, size_t>,
        std::vector<std::pair<uint32_t, size_t>>,
        std::greater<std::pair<uint32_t, size_t>>
    > min_heap;

    for (size_t i = 0; i < cnt_batch_; ++i) {
        
        std::string batch_file("tmp/batch" + std::to_string(i) + ".txt");
        auto file_path = GetAbsolutePath(batch_file);
        batch_streams.emplace_back(file_path);

        if (!batch_streams[i].is_open()) {
            std::runtime_error("Can't create and write to temporary file");
        }

        uint32_t value;
        if (batch_streams[i] >> value) {
            min_heap.emplace(value, i);
        }
    }

    std::ofstream out(output_file.data());
    if (!out.is_open()) {
        throw std::runtime_error("Can't write to output file");
    }

    while (!min_heap.empty()){
        auto [value, index] = min_heap.top();
        min_heap.pop();

        out << value << " ";

        uint32_t new_value;
        if (batch_streams[index] >> new_value) {
            min_heap.emplace(new_value, index);
        }
    }

    for (size_t i = 0; i < cnt_batch_; ++i) {
        if (!batch_streams[i].eof()) {
            throw std::runtime_error("Can't read all data from temporary file");
        }
        batch_streams[i].close();
    }

    out.close();
}

void Tape::ClearTempDirectory() {
    for (size_t i = 0; i < cnt_batch_; ++i) {
        
        std::string batch_file("tmp/batch" + std::to_string(i) + ".txt");
        auto file_path = GetAbsolutePath(batch_file);
        fs::remove(file_path);
        
    }
}