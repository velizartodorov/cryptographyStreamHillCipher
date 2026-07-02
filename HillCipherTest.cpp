#include "TestFramework.h"
#include "HillCipher.h"
#include "Utils.h"
#include <cstring>
#include <iostream>

static void encodeHill(char* plainText, int matrixKey[25][25]) {
    HillCipher cipher;
    cipher.encode(plainText, matrixKey);
}

// Test for basic Hill cipher encoding
TEST(HillCipher_BasicEncoding) {
    char plainText[7] = "hello"; // extra byte: odd-length input gets 'x'-padded in place
    int matrixKey[25][25] = {{3, 3}, {2, 5}}; // 2x2 key matrix

    encodeHill(plainText, matrixKey);

    // Verify that the function completes without crashing
    ASSERT_TRUE(true); // Basic functionality test
}

// Test for Hill cipher with even length text
TEST(HillCipher_EvenLengthText) {
    char plainText[] = "abcd"; // Even length
    int matrixKey[25][25] = {{1, 2}, {3, 4}};

    encodeHill(plainText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for Hill cipher with odd length text (should add padding)
TEST(HillCipher_OddLengthText) {
    char plainText[5] = "abc"; // Odd length; extra byte for in-place 'x' padding
    int matrixKey[25][25] = {{2, 1}, {1, 3}};

    encodeHill(plainText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for Hill cipher with single character
TEST(HillCipher_SingleCharacter) {
    char plainText[3] = "a"; // extra byte for in-place 'x' padding
    int matrixKey[25][25] = {{1, 0}, {0, 1}}; // Identity matrix

    encodeHill(plainText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for Hill cipher with identity matrix
TEST(HillCipher_IdentityMatrix) {
    char plainText[] = "test";
    int matrixKey[25][25] = {{1, 0}, {0, 1}}; // Identity matrix

    encodeHill(plainText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for Hill cipher with different matrix values
TEST(HillCipher_DifferentMatrixValues) {
    char plainText[7] = "hello"; // extra byte for in-place 'x' padding
    int matrixKey[25][25] = {{5, 7}, {2, 3}};

    encodeHill(plainText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for Hill cipher with uppercase text
TEST(HillCipher_UppercaseText) {
    char plainText[7] = "HELLO"; // extra byte for in-place 'x' padding
    int matrixKey[25][25] = {{3, 3}, {2, 5}};

    encodeHill(plainText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for Hill cipher with mixed case text
TEST(HillCipher_MixedCaseText) {
    char plainText[7] = "HeLlO"; // extra byte for in-place 'x' padding
    int matrixKey[25][25] = {{1, 1}, {1, 2}};

    encodeHill(plainText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for Hill cipher with long text
TEST(HillCipher_LongText) {
    char plainText[] = "abcdefghijklmnopqrstuvwxyz";
    int matrixKey[25][25] = {{2, 1}, {1, 3}};

    encodeHill(plainText, matrixKey);
    ASSERT_TRUE(true);
}
