#pragma once 

#include <vector>

#include "../../domain/services/TapeInterface.h"
#include "../../domain/services/EnvFileParserInterface.h"

class Tape : public TapeInterface {
private:

    size_t cnt_batch_;
    std::shared_ptr<EnvFileParserInterface> parser_;
    ConfigurationProperties properties_;

public:

    Tape(std::shared_ptr<EnvFileParserInterface> parser);

    void SetUpTape(std::string_view env_file) override;
    void SortFile(std::string_view input_file, std::string_view output_file) override;

private:

    std::string GetAbsolutePath(std::string_view path);
    void CreateBatchesFromInput(std::string_view input_file);
    void SortAndSaveBatch(std::vector<uint32_t>& batch_values, size_t batch_size);
    void MergeBatches(std::string_view output_file);

};