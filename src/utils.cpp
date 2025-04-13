#include "utils.hpp"
#include <sstream>
#include <iomanip>

namespace chacha20 {

// Rotates a 32-bit integer left by n bits
uint32_t rotl32(uint32_t value, int shift) {
    return (value << shift) | (value >> (32 - shift));
}

// Converts hex string to bytes
std::vector<uint8_t> hexToBytes(const std::string& hex) {
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        uint8_t byte = std::stoi(hex.substr(i, 2), nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

// Converts bytes to hex string
std::string bytesToHex(const std::vector<uint8_t>& bytes) {
    std::ostringstream oss;
    for (uint8_t byte : bytes) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    return oss.str();
}

// Converts string to vector of bytes
std::vector<uint8_t> stringToBytes(const std::string& str) {
    std::vector<uint8_t> bytes(str.begin(), str.end());
    return bytes;
}

// Converts bytes to string
std::string bytesToString(const std::vector<uint8_t>& bytes) {
    return std::string(bytes.begin(), bytes.end());
}

} // namespace chacha20
