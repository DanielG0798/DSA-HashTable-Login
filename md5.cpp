#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "md5.h"
using namespace std;

typedef unsigned int uint4;

class MD5 {
private:
    unsigned char buffer[64], digest[16];
    uint4 state[4], count[2];
    bool finalized;

    void transform(const uint4 block[16]);
    void encode(const uint4* input, unsigned char* output, size_t length) const;
    void decode(const unsigned char* input, uint4* output, size_t length) const;

public:
    MD5();
    void update(const unsigned char* input, size_t length);
    void finalize();
    string hexdigest() const;
};

inline static uint4 F(uint4 x, uint4 y, uint4 z) { return (x & y) | (~x & z); }
inline static uint4 G(uint4 x, uint4 y, uint4 z) { return (x & z) | (y & ~z); }
inline static uint4 H(uint4 x, uint4 y, uint4 z) { return x ^ y ^ z; }
inline static uint4 I(uint4 x, uint4 y, uint4 z) { return y ^ (x | ~z); }

inline static uint4 rotate_left(uint4 x, int n) { return (x << n) | (x >> (32 - n)); }

inline static void FF(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
    a += F(b, c, d) + x + ac;
    a = rotate_left(a, s) + b;
}
inline static void GG(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
    a += G(b, c, d) + x + ac;
    a = rotate_left(a, s) + b;
}
inline static void HH(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
    a += H(b, c, d) + x + ac;
    a = rotate_left(a, s) + b;
}
inline static void II(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
    a += I(b, c, d) + x + ac;
    a = rotate_left(a, s) + b;
}

MD5::MD5() {
    for (int i = 0; i < 16; i++) {
        buffer[i] = NULL;
        digest[i] = NULL;
    }
    for (int i = 16; i < 64; i++) {
        buffer[i] = NULL;
    }
    finalized = false;
    count[0] = count[1] = 0;
    state[0] = 0x67452301;
    state[1] = 0xefcdab89;
    state[2] = 0x98badcfe;
    state[3] = 0x10325476;
}

void MD5::update(const unsigned char* input, size_t length) {
    size_t index = count[0] / 8 % 64;

    if ((count[0] += (uint4)length << 3) < ((uint4)length << 3))
        count[1]++;
    count[1] += (uint4)length >> 29;

    size_t partLen = 64 - index;
    size_t i = 0;

    if (length >= partLen) {
        memcpy(&buffer[index], input, partLen);
        transform((uint4*)buffer);

        for (i = partLen; i + 63 < length; i += 64)
            transform((uint4*)&input[i]);

        index = 0;
    }

    memcpy(&buffer[index], &input[i], length - i);
}

void MD5::finalize() {
    static unsigned char padding[64] = { 0x80 };
    unsigned char bits[8];
    encode(count, bits, 8);

    size_t index = count[0] / 8 % 64;
    size_t padLen = (index < 56) ? (56 - index) : (120 - index);
    update(padding, padLen);
    update(bits, 8);

    encode(state, digest, 16);
    finalized = true;
}

void MD5::transform(const uint4 block[16]) {
    uint4 a = state[0], b = state[1], c = state[2], d = state[3];

    FF(a, b, c, d, block[0], 7, 0xd76aa478);
    FF(d, a, b, c, block[1], 12, 0xe8c7b756);
    FF(c, d, a, b, block[2], 17, 0x242070db);
    FF(b, c, d, a, block[3], 22, 0xc1bdceee);
    FF(a, b, c, d, block[4], 7, 0xf57c0faf);
    FF(d, a, b, c, block[5], 12, 0x4787c62a);
    FF(c, d, a, b, block[6], 17, 0xa8304613);
    FF(b, c, d, a, block[7], 22, 0xfd469501);
    FF(a, b, c, d, block[8], 7, 0x698098d8);
    FF(d, a, b, c, block[9], 12, 0x8b44f7af);
    FF(c, d, a, b, block[10], 17, 0xffff5bb1);
    FF(b, c, d, a, block[11], 22, 0x895cd7be);
    FF(a, b, c, d, block[12], 7, 0x6b901122);
    FF(d, a, b, c, block[13], 12, 0xfd987193);
    FF(c, d, a, b, block[14], 17, 0xa679438e);
    FF(b, c, d, a, block[15], 22, 0x49b40821);

    GG(a, b, c, d, block[1], 5, 0xf61e2562);
    GG(d, a, b, c, block[6], 9, 0xc040b340);
    GG(c, d, a, b, block[11], 14, 0x265e5a51);
    GG(b, c, d, a, block[0], 20, 0xe9b6c7aa);
    GG(a, b, c, d, block[5], 5, 0xd62f105d);
    GG(d, a, b, c, block[10], 9, 0x02441453);
    GG(c, d, a, b, block[15], 14, 0xd8a1e681);
    GG(b, c, d, a, block[4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, block[9], 5, 0x21e1cde6);
    GG(d, a, b, c, block[14], 9, 0xc33707d6);
    GG(c, d, a, b, block[3], 14, 0xf4d50d87);
    GG(b, c, d, a, block[8], 20, 0x455a14ed);
    GG(a, b, c, d, block[13], 5, 0xa9e3e905);
    GG(d, a, b, c, block[2], 9, 0xfcefa3f8);
    GG(c, d, a, b, block[7], 14, 0x676f02d9);
    GG(b, c, d, a, block[12], 20, 0x8d2a4c8a);

    HH(a, b, c, d, block[5], 4, 0xfffa3942);
    HH(d, a, b, c, block[8], 11, 0x8771f681);
    HH(c, d, a, b, block[11], 16, 0x6d9d6122);
    HH(b, c, d, a, block[14], 23, 0xfde5380c);
    HH(a, b, c, d, block[1], 4, 0xa4beea44);
    HH(d, a, b, c, block[4], 11, 0x4bdecfa9);
    HH(c, d, a, b, block[7], 16, 0xf6bb4b60);
    HH(b, c, d, a, block[10], 23, 0xbebfbc70);
    HH(a, b, c, d, block[13], 4, 0x289b7ec6);
    HH(d, a, b, c, block[0], 11, 0xeaa127fa);
    HH(c, d, a, b, block[3], 16, 0xd4ef3085);
    HH(b, c, d, a, block[6], 23, 0x04881d05);
    HH(a, b, c, d, block[9], 4, 0xd9d4d039);
    HH(d, a, b, c, block[12], 11, 0xe6db99e5);
    HH(c, d, a, b, block[15], 16, 0x1fa27cf8);
    HH(b, c, d, a, block[2], 23, 0xc4ac5665);

    II(a, b, c, d, block[0], 6, 0xf4292244);
    II(d, a, b, c, block[7], 10, 0x432aff97);
    II(c, d, a, b, block[14], 15, 0xab9423a7);
    II(b, c, d, a, block[5], 21, 0xfc93a039);
    II(a, b, c, d, block[12], 6, 0x655b59c3);
    II(d, a, b, c, block[3], 10, 0x8f0ccc92);
    II(c, d, a, b, block[10], 15, 0xffeff47d);
    II(b, c, d, a, block[1], 21, 0x85845dd1);
    II(a, b, c, d, block[8], 6, 0x6fa87e4f);
    II(d, a, b, c, block[15], 10, 0xfe2ce6e0);
    II(c, d, a, b, block[6], 15, 0xa3014314);
    II(b, c, d, a, block[13], 21, 0x4e0811a1);
    II(a, b, c, d, block[4], 6, 0xf7537e82);
    II(d, a, b, c, block[11], 10, 0xbd3af235);
    II(c, d, a, b, block[2], 15, 0x2ad7d2bb);
    II(b, c, d, a, block[9], 21, 0xeb86d391);

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

void MD5::encode(const uint4* input, unsigned char* output, size_t length) const {
    for (size_t i = 0, j = 0; j < length; ++i, j += 4) {
        output[j] = (unsigned char)(input[i] & 0xff);
        output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
        output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
        output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
    }
}

void MD5::decode(const unsigned char* input, uint4* output, size_t length) const {
    for (size_t i = 0, j = 0; j < length; ++i, j += 4) {
        output[i] = ((uint4)input[j]) |
                    (((uint4)input[j + 1]) << 8) |
                    (((uint4)input[j + 2]) << 16) |
                    (((uint4)input[j + 3]) << 24);
    }
}

string MD5::hexdigest() const {
    ostringstream result;
    for (int i = 0; i < 16; ++i) {
        result << hex << setw(2) << setfill('0') << (int)digest[i];
    }
    return result.str();
}

string md5(const string& str) {
    MD5 md5;
    md5.update(reinterpret_cast<const unsigned char*>(str.c_str()), str.length());
    md5.finalize();
    return md5.hexdigest();
}
