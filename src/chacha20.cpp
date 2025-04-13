#include "chacha20.hpp"
#include <iostream>
#include <stdexcept>
#include <cstring>

// Helper function to rotate a 32-bit integer left by n bits
uint32_t rotl32(uint32_t value, int shift) {
    return (value << shift) | (value >> (32 - shift));
}

// Quarter round operation as defined by ChaCha20
void quarterround(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d) {
    *a += *b; *d ^= *a; *d = rotl32(*d, 16);
    *c += *d; *b ^= *c; *b = rotl32(*b, 12);
    *a += *b; *d ^= *a; *d = rotl32(*d, 8);
    *c += *d; *b ^= *c; *b = rotl32(*b, 7);
}

// Generates a single ChaCha20 block (64 bytes)
void chacha20_block(uint32_t state[16], uint8_t output[64]) {
    uint32_t working_state[16];
    std::memcpy(working_state, state, 64);

    for (int i = 0; i < 10; ++i) {
        quarterround(&working_state[0], &working_state[4], &working_state[8], &working_state[12]);
        quarterround(&working_state[1], &working_state[5], &working_state[9], &working_state[13]);
        quarterround(&working_state[2], &working_state[6], &working_state[10], &working_state[14]);
        quarterround(&working_state[3], &working_state[7], &working_state[11], &working_state[15]);

        quarterround(&working_state[0], &working_state[5], &working_state[10], &working_state[15]);
        quarterround(&working_state[1], &working_state[6], &working_state[11], &working_state[12]);
        quarterround(&working_state[2], &working_state[7], &working_state[8], &working_state[13]);
        quarterround(&working_state[3], &working_state[4], &working_state[9], &working_state[14]);
    }

    for (int i = 0; i < 16; ++i) {
        working_state[i] += state[i];
    }

    std::memcpy(output, working_state, 64);
}

// Encrypts or decrypts the input using ChaCha20
std::vector<uint8_t> chacha20::encrypt(
    const std::vector<uint8_t>& plaintext,
    const std::vector<uint8_t>& key,
    const std::vector<uint8_t>& nonce,
    uint32_t counter) {

    if (key.size() != KEY_SIZE || nonce.size() != NONCE_SIZE) {
        throw std::invalid_argument("Invalid key or nonce size");
    }

    std::vector<uint8_t> ciphertext(plaintext.size());
    uint8_t keystream[BLOCK_SIZE];
    uint32_t state[16] = {
        0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,  // constant "expand 32-byte k"
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0               // Key and counter will go here
    };

    std::memcpy(&state[4], key.data(), KEY_SIZE);
    std::memcpy(&state[12], nonce.data(), NONCE_SIZE);

    size_t input_pos = 0;
    while (input_pos < plaintext.size()) {
        state[14] = counter++;  // Update counter for each block

        chacha20_block(state, keystream);  // Generate a keystream block

        size_t remaining = std::min(plaintext.size() - input_pos, BLOCK_SIZE);
        for (size_t i = 0; i < remaining; ++i) {
            ciphertext[input_pos + i] = plaintext[input_pos + i] ^ keystream[i];
        }

        input_pos += remaining;
    }

    return ciphertext;
}

// Overload for encrypting strings
std::string chacha20::encrypt(
    const std::string& plaintext,
    const std::vector<uint8_t>& key,
    const std::vector<uint8_t>& nonce,
    uint32_t counter) {

    std::vector<uint8_t> plaintext_bytes(plaintext.begin(), plaintext.end());
    std::vector<uint8_t> ciphertext = encrypt(plaintext_bytes, key, nonce, counter);

    return std::string(ciphertext.begin(), ciphertext.end());
}
