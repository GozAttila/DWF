#pragma once

#include <cstdint>

uint32_t murmur_hash3(const void* key, int len, uint32_t seed);