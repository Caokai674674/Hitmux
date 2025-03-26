#ifndef SHA256_H
#define SHA256_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

const unsigned int K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

const unsigned int H[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

unsigned int rotr(unsigned int n, unsigned int d) {
    return (n >> d) | (n << (32 - d));
}

unsigned int sigma0(unsigned int x) {
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

unsigned int sigma1(unsigned int x) {
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

unsigned int SIGMA0(unsigned int x) {
    return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
}

unsigned int SIGMA1(unsigned int x) {
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}

unsigned int ch(unsigned int x, unsigned int y, unsigned int z) {
    return (x & y) ^ (~x & z);
}

unsigned int maj(unsigned int x, unsigned int y, unsigned int z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

std::vector<unsigned char> stringToBytes(const std::string& str) {
    std::vector<unsigned char> bytes(str.begin(), str.end());
    return bytes;
}

std::string bytesToHex(const std::vector<unsigned char>& bytes) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (unsigned char byte : bytes) {
        ss << std::setw(2) << static_cast<int>(byte);
    }
    return ss.str();
}

std::string sha256(const std::string& message) {
    std::vector<unsigned char> bytes = stringToBytes(message);
    size_t original_length_bits = bytes.size() * 8;

    bytes.push_back(0x80);
    while ((bytes.size() * 8) % 512 != 448) {
        bytes.push_back(0x00);
    }

    for (int i = 7; i >= 0; --i) {
        bytes.push_back((original_length_bits >> (i * 8)) & 0xFF);
    }

    size_t num_blocks = bytes.size() / 64;
    std::vector<unsigned int> current_hash(H, H + 8);

    for (size_t i = 0; i < num_blocks; ++i) {
        std::vector<unsigned int> w(64);
        for (int j = 0; j < 16; ++j) {
            w[j] = (bytes[i * 64 + j * 4] << 24) |
                   (bytes[i * 64 + j * 4 + 1] << 16) |
                   (bytes[i * 64 + j * 4 + 2] << 8) |
                   (bytes[i * 64 + j * 4 + 3]);
        }
        for (int j = 16; j < 64; ++j) {
            w[j] = sigma1(w[j - 2]) + w[j - 7] + sigma0(w[j - 15]) + w[j - 16];
        }

        unsigned int a = current_hash[0];
        unsigned int b = current_hash[1];
        unsigned int c = current_hash[2];
        unsigned int d = current_hash[3];
        unsigned int e = current_hash[4];
        unsigned int f = current_hash[5];
        unsigned int g = current_hash[6];
        unsigned int h = current_hash[7];

        for (int j = 0; j < 64; ++j) {
            unsigned int s1 = SIGMA1(e) ^ ch(e, f, g);
            unsigned int temp1 = h + s1 + K[j] + w[j];
            unsigned int s0 = SIGMA0(a) ^ maj(a, b, c);
            unsigned int temp2 = s0 + d;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        current_hash[0] += a;
        current_hash[1] += b;
        current_hash[2] += c;
        current_hash[3] += d;
        current_hash[4] += e;
        current_hash[5] += f;
        current_hash[6] += g;
        current_hash[7] += h;
    }

    std::vector<unsigned char> result_bytes;
    for (unsigned int val : current_hash) {
        for (int i = 3; i >= 0; --i) {
            result_bytes.push_back((val >> (i * 8)) & 0xFF);
        }
    }

    return bytesToHex(result_bytes);
}

#endif