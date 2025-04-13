#ifndef CHACHA20_UTILS_HPP
#define CHACHA20_UTILS_HPP

#include <cstdint>
#include <vector>
#include <string>

namespace chacha20 {

// Rotates a 32-bit integer left by n bits
uint32_t rotl32(uint32_t value, int shift);

// Converts hex string to bytes
std::vector<uint8_t> hexToBytes(const std::string& hex);

// Converts bytes to hex string
std::string bytesToHex(const std::vector<uint8_t>& bytes);

// Converts string to vector of bytes
std::vector<uint8_t> stringToBytes(const std::string& str);

// Converts bytes to string
std::string bytesToString(const std::vector<uint8_t>& bytes);

} // namespace chacha20

#endif
