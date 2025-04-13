#include "input.hpp"
#include <iostream>
#include <fstream>
#include <random>
#include <cstring>
#include <cstdlib>
#include <vector>

#ifdef _WIN32
    #include <Windows.h>
    #include <Wincrypt.h>
#else
    #include <unistd.h>
#endif

// Returns a vector of uint8_t containing the user's key (password)
std::vector<uint8_t> get_key() {
    std::vector<uint8_t> key(32, 0);  // Allocate 32 bytes for the key (default to 0)

    std::cout << "Enter password: ";
    std::string buffer;
    std::getline(std::cin, buffer);  // Read the entire line as a string

    size_t len = buffer.length();
    if (len > 32) len = 32;  // Limit password length to 32 bytes

    // Copy password into the key vector
    std::memcpy(key.data(), buffer.c_str(), len);

    return key;
}

// Returns a vector of uint8_t containing the nonce (12 random bytes)
std::vector<uint8_t> get_nonce() {
    std::vector<uint8_t> nonce(12, 0);  // Allocate 12 bytes for the nonce

#ifdef _WIN32
    // Windows-specific: Use CryptGenRandom for random data
    HCRYPTPROV cryptProv;
    if (CryptAcquireContext(&cryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        if (!CryptGenRandom(cryptProv, nonce.size(), nonce.data())) {
            std::cerr << "Error: Failed to generate random data on Windows.\n";
        }
        CryptReleaseContext(cryptProv, 0);
    } else {
        std::cerr << "Warning: CryptAcquireContext failed, using rand() instead.\n";
        // Fallback to using rand()
        for (size_t i = 0; i < nonce.size(); ++i) {
            nonce[i] = static_cast<uint8_t>(std::rand());
        }
    }
#else
    // Unix-like systems (Linux/macOS): Try to get random data from /dev/urandom
    std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
    if (urandom.is_open()) {
        urandom.read(reinterpret_cast<char*>(nonce.data()), nonce.size());
        urandom.close();
        if (urandom.gcount() != nonce.size()) {
            std::cerr << "Error: Could not read enough bytes from /dev/urandom\n";
        }
    } else {
        std::cerr << "Warning: /dev/urandom could not be used. Using stdlib's rand() instead.\n";
        // Fallback to using rand()
        for (size_t i = 0; i < nonce.size(); ++i) {
            nonce[i] = static_cast<uint8_t>(std::rand());
        }
    }
#endif

    return nonce;
}
