#pragma once 

#include <vector>

#include "TapeInterface.h"
#include "../parser/EnvFileParser.h"

class Tape : public TapeInterface {
private:

    size_t cnt_batch_;
    EnvFileParser parser_;
    ConfigurationProperties properties_;

public:

    Tape();

    void SetUpTape(std::string_view env_file) override;
    void SortFile(std::string_view input_file, std::string_view output_file) override;

private:

    void CreateBatchesFromInput(std::string_view input_file);
    void SortAndSaveBatch(std::vector<uint32_t>& batch_values, size_t batch_size);
    void MergeBatches(std::string_view output_file);

};