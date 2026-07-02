#include "TestFramework.h"
#include "HillCipher.h"
#include "Utils.h"
#include "Matrix.h"
#include <string>

static void encodeHill(string& plainText, const Matrix& matrixKey) {
    HillCipher cipher;
    cipher.encode(plainText, matrixKey);
}

struct HillCase {
    const char* name;
    const char* plainText;
    Matrix matrixKey;
};

static const HillCase hillCases[] = {
    {"BasicEncoding", "hello", {{3, 3}, {2, 5}}},
    {"EvenLengthText", "abcd", {{1, 2}, {3, 4}}},
    {"OddLengthText", "abc", {{2, 1}, {1, 3}}},
    {"SingleCharacter", "a", {{1, 0}, {0, 1}}}, // identity matrix
    {"IdentityMatrix", "test", {{1, 0}, {0, 1}}},
    {"DifferentMatrixValues", "hello", {{5, 7}, {2, 3}}},
    {"UppercaseText", "HELLO", {{3, 3}, {2, 5}}},
    {"MixedCaseText", "HeLlO", {{1, 1}, {1, 2}}},
    {"LongText", "abcdefghijklmnopqrstuvwxyz", {{2, 1}, {1, 3}}},
    {"ThreeByThreeMatrix", "abcdefghi", {{1, 2, 3}, {0, 1, 4}, {5, 6, 0}}}, // exercises N = 3
    {"OneByOneMatrix", "hello", {{7}}},                                    // exercises N = 1
};

// Test for Hill cipher encoding across text lengths, casing, and key matrix
// sizes (matrix_key's dimensions drive the block size N — see ThreeByThreeMatrix
// and OneByOneMatrix). Every case just needs to complete without crashing;
// non-multiple-of-N inputs get 'x'-padded in place by HillCipher::encode itself.
TEST(HillCipher_AllCases) {
    for (const auto& tc : hillCases) {
        string plainText = tc.plainText;

        try {
            encodeHill(plainText, tc.matrixKey);
        } catch (...) {
            throw runtime_error(string("Case '") + tc.name + "' threw during encoding");
        }
    }
}
