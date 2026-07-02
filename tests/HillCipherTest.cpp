#include "TestFramework.h"
#include "HillCipher.h"
#include "Utils.h"
#include <cstring>
#include <iostream>

static void encodeHill(char* plainText, int matrixKey[25][25]) {
    HillCipher cipher;
    cipher.encode(plainText, matrixKey);
}

struct HillCase {
    const char* name;
    const char* plainText;
    int a, b, c, d; // 2x2 key matrix: {{a, b}, {c, d}}
};

static const HillCase hillCases[] = {
    {"BasicEncoding", "hello", 3, 3, 2, 5},
    {"EvenLengthText", "abcd", 1, 2, 3, 4},
    {"OddLengthText", "abc", 2, 1, 1, 3},
    {"SingleCharacter", "a", 1, 0, 0, 1}, // identity matrix
    {"IdentityMatrix", "test", 1, 0, 0, 1},
    {"DifferentMatrixValues", "hello", 5, 7, 2, 3},
    {"UppercaseText", "HELLO", 3, 3, 2, 5},
    {"MixedCaseText", "HeLlO", 1, 1, 1, 2},
    {"LongText", "abcdefghijklmnopqrstuvwxyz", 2, 1, 1, 3},
};

// Test for Hill cipher encoding across text lengths, casing, and key matrices.
// Every case just needs to complete without crashing — odd-length inputs get
// 'x'-padded in place, so the buffer is sized with slack for that.
TEST(HillCipher_AllCases) {
    for (const auto& tc : hillCases) {
        char plainText[40];
        strcpy_s(plainText, sizeof(plainText), tc.plainText);
        int matrixKey[25][25] = {{tc.a, tc.b}, {tc.c, tc.d}};

        try {
            encodeHill(plainText, matrixKey);
        } catch (...) {
            throw runtime_error(string("Case '") + tc.name + "' threw during encoding");
        }
    }
}
