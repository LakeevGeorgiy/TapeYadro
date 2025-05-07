#pragma once

#include <string_view>

class TapeInterface {
public:

    virtual void SetUpTape(std::string_view env_file) = 0;
    virtual void SortFile(std::string_view input_file, std::string_view output_file) = 0;
    virtual ~TapeInterface() = default;
};