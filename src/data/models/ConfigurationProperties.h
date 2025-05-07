#pragma once

#include <cstdint>
#include <string>

class ConfigurationProperties {
public:

    uint32_t memory_limit_;
    uint32_t read_latency_;
    uint32_t write_latency_;
    uint32_t rewind_latency_;
    uint32_t shift_latency_;

public:

    ConfigurationProperties() = default;

};