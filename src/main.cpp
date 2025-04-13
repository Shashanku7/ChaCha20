#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

#include "input.hpp"
#include "chacha20.hpp"
#include "utils.hpp"

using namespace chacha20;

int main(int argc, char** argv) {
    // 1. Validate command line arguments
    if (argc != 3 || (strcmp(argv[2], "e") != 0 && strcmp(argv[2], "d") != 0)) {
        std::cerr << "Usage: " << argv[0] << " <filename> <e|d>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    bool encrypting = (strcmp(argv[2], "e") == 0);

    // 2. Open input file
    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open input file: " << inputFile << std::endl;
        return 1;
    }

    // 3. Create output filename and open file
    std::string outputFile;
    if (encrypting)
        outputFile = inputFile + ".enc";
    else
        outputFile = inputFile.substr(0, inputFile.size() - 4) + ".dec";

    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputFile << std::endl;
        return 1;
    }

    // 4. Get key and nonce
    std::vector<uint8_t> key = get_key();
    std::vector<uint8_t> nonce(NONCE_SIZE);

    if (encrypting) {
        std::vector<uint8_t> gen_nonce = get_nonce();
        std::copy(gen_nonce.begin(), gen_nonce.end(), nonce.begin());
        outFile.write(reinterpret_cast<char*>(nonce.data()), NONCE_SIZE);
    } else {
        inFile.read(reinterpret_cast<char*>(nonce.data()), NONCE_SIZE);
        if (inFile.gcount() != NONCE_SIZE) {
            std::cerr << "Failed to read nonce from file." << std::endl;
            return 1;
        }
    }

    // 5. Encrypt/decrypt in 64-byte chunks
    const size_t bufferSize = BLOCK_SIZE;
    std::vector<uint8_t> buffer(bufferSize);
    uint32_t counter = 0;

    while (inFile.read(reinterpret_cast<char*>(buffer.data()), bufferSize) || inFile.gcount() > 0) {
        size_t bytesRead = inFile.gcount();
        buffer.resize(bytesRead);

        std::vector<uint8_t> result = encrypt(buffer, key, nonce, counter++);
        outFile.write(reinterpret_cast<const char*>(result.data()), result.size());

        buffer.resize(bufferSize); // Reset buffer size for next round
    }

    std::cout << (encrypting ? "Encryption" : "Decryption") << " complete: " << outputFile << std::endl;

    inFile.close();
    outFile.close();
    return 0;
}
