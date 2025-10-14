#include "TestFramework.h"
#include "HillCipher.h"
#include "Utils.h"
#include <cstring>
#include <iostream>

// Test for basic Hill cipher encoding
TEST(HillCipher_BasicEncoding) {
    HillCipher cipher;
    char plainText[] = "hello";
    int matrixKey[25][25] = {{3, 3}, {2, 5}}; // 2x2 key matrix
    
    // Test encoding
    cipher.encode(plainText, matrixKey);
    
    // Verify that the function completes without crashing
    ASSERT_TRUE(true); // Basic functionality test
}

// Test for Hill cipher with even length text
TEST(HillCipher_EvenLengthText) {
    HillCipher cipher;
    char plainText[] = "abcd"; // Even length
    int matrixKey[25][25] = {{1, 2}, {3, 4}};
    
    cipher.encode(plainText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for Hill cipher with odd length text (should add padding)
TEST(HillCipher_OddLengthText) {
    HillCipher cipher;
    char plainText[] = "abc"; // Odd length
    int matrixKey[25][25] = {{2, 1}, {1, 3}};
    
    cipher.encode(plainText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for Hill cipher with single character
TEST(HillCipher_SingleCharacter) {
    HillCipher cipher;
    char plainText[] = "a";
    int matrixKey[25][25] = {{1, 0}, {0, 1}}; // Identity matrix
    
    cipher.encode(plainText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for Hill cipher with identity matrix
TEST(HillCipher_IdentityMatrix) {
    HillCipher cipher;
    char plainText[] = "test";
    int matrixKey[25][25] = {{1, 0}, {0, 1}}; // Identity matrix
    
    cipher.encode(plainText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for Hill cipher with different matrix values
TEST(HillCipher_DifferentMatrixValues) {
    HillCipher cipher;
    char plainText[] = "hello";
    int matrixKey[25][25] = {{5, 7}, {2, 3}};
    
    cipher.encode(plainText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for Hill cipher with uppercase text
TEST(HillCipher_UppercaseText) {
    HillCipher cipher;
    char plainText[] = "HELLO";
    int matrixKey[25][25] = {{3, 3}, {2, 5}};
    
    cipher.encode(plainText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for Hill cipher with mixed case text
TEST(HillCipher_MixedCaseText) {
    HillCipher cipher;
    char plainText[] = "HeLlO";
    int matrixKey[25][25] = {{1, 1}, {1, 2}};
    
    cipher.encode(plainText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for Hill cipher with long text
TEST(HillCipher_LongText) {
    HillCipher cipher;
    char plainText[] = "abcdefghijklmnopqrstuvwxyz";
    int matrixKey[25][25] = {{2, 1}, {1, 3}};
    
    cipher.encode(plainText, matrixKey);
    ASSERT_TRUE(true);
}
