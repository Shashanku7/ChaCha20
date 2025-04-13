#ifndef CHACHA20_HPP
#define CHACHA20_HPP

#include <cstdint>
#include <vector>
#include <string>

namespace chacha20 {

constexpr size_t KEY_SIZE = 32;     // 256-bit key
constexpr size_t NONCE_SIZE = 12;   // 96-bit nonce
constexpr size_t BLOCK_SIZE = 64;   // 512-bit block

// Encrypt or decrypt input using ChaCha20
std::vector<uint8_t> encrypt(
    const std::vector<uint8_t>& plaintext,
    const std::vector<uint8_t>& key,
    const std::vector<uint8_t>& nonce,
    uint32_t counter = 0
);

// Overload for string input/output
std::string encrypt(
    const std::string& plaintext,
    const std::vector<uint8_t>& key,
    const std::vector<uint8_t>& nonce,
    uint32_t counter = 0
);

} // namespace chacha20

#endif // CHACHA20_H
