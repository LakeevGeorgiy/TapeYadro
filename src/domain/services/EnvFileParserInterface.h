#pragma once
#include "../../data/models/ConfigurationProperties.h"

class EnvFileParserInterface {
public:

    virtual ConfigurationProperties ParseEnvFile(std::string_view path) = 0;

};