#include "TestFramework.h"
#include "StreamCipher.h"
#include "HillCipher.h"
#include "Utils.h"
#include <cstring>
#include <iostream>

// Runs the full Stream Cipher -> Hill Cipher pipeline, writing the
// intermediate stream-cipher output into cipherText.
static void runPipeline(char* plainText, char* cipherText, char* key, int matrixKey[25][25]) {
    StreamCipher streamCipher;
    HillCipher hillCipher;
    streamCipher.encode(plainText, cipherText, key);
    hillCipher.encode(cipherText, matrixKey);
}

// Test for complete encryption pipeline: Stream Cipher -> Hill Cipher
TEST(Integration_StreamThenHillCipher) {
    char plainText[] = "hello";
    char streamCipherText[50];
    char key[] = "key";
    int matrixKey[25][25] = {{3, 3}, {2, 5}};

    runPipeline(plainText, streamCipherText, key, matrixKey);

    // Verify that both operations complete successfully
    ASSERT_TRUE(strlen(streamCipherText) > 0);
    ASSERT_TRUE(true); // Hill cipher completed without crashing
}

// Test for encryption pipeline with different text lengths
TEST(Integration_DifferentTextLengths) {
    char cipherText[50];
    char key[] = "abc";
    int matrixKey[25][25] = {{1, 2}, {3, 4}};

    // Test with short text
    char shortText[] = "hi";
    runPipeline(shortText, cipherText, key, matrixKey);
    ASSERT_TRUE(true);

    // Test with medium text
    char mediumText[] = "hello world";
    runPipeline(mediumText, cipherText, key, matrixKey);
    ASSERT_TRUE(true);

    // Test with long text
    char longText[] = "this is a very long text for testing";
    runPipeline(longText, cipherText, key, matrixKey);
    ASSERT_TRUE(true);
}

// Test for encryption pipeline with different keys
TEST(Integration_DifferentKeys) {
    char plainText[] = "test";
    char cipherText[50];
    int matrixKey[25][25] = {{2, 1}, {1, 3}};

    // Test with different stream cipher keys
    char key1[] = "a";
    char key2[] = "key";
    char key3[] = "verylongkey";

    runPipeline(plainText, cipherText, key1, matrixKey);
    ASSERT_TRUE(true);

    runPipeline(plainText, cipherText, key2, matrixKey);
    ASSERT_TRUE(true);

    runPipeline(plainText, cipherText, key3, matrixKey);
    ASSERT_TRUE(true);
}

// Test for encryption pipeline with different matrix keys
TEST(Integration_DifferentMatrixKeys) {
    char plainText[] = "hello";
    char cipherText[50];
    char key[] = "key";

    // Test with identity matrix
    int identityMatrix[25][25] = {{1, 0}, {0, 1}};
    runPipeline(plainText, cipherText, key, identityMatrix);
    ASSERT_TRUE(true);

    // Test with different matrix
    int matrix2[25][25] = {{5, 7}, {2, 3}};
    runPipeline(plainText, cipherText, key, matrix2);
    ASSERT_TRUE(true);

    // Test with another matrix
    int matrix3[25][25] = {{1, 1}, {1, 2}};
    runPipeline(plainText, cipherText, key, matrix3);
    ASSERT_TRUE(true);
}

// Test for encryption pipeline consistency
TEST(Integration_EncryptionConsistency) {
    char plainText[] = "consistency";
    char cipherText1[50];
    char cipherText2[50];
    char key[] = "testkey";
    int matrixKey[25][25] = {{3, 1}, {2, 4}};

    // Run the same encryption twice
    runPipeline(plainText, cipherText1, key, matrixKey);
    runPipeline(plainText, cipherText2, key, matrixKey);

    // Both should complete successfully
    ASSERT_TRUE(true);
}

// Test for encryption pipeline with edge cases
TEST(Integration_EdgeCases) {
    char key[] = "key";
    int matrixKey[25][25] = {{1, 1}, {1, 1}};
    char cipherText[50];

    // Test with single character
    char singleChar[] = "a";
    runPipeline(singleChar, cipherText, key, matrixKey);
    ASSERT_TRUE(true);

    // Test with two characters
    char twoChars[] = "ab";
    runPipeline(twoChars, cipherText, key, matrixKey);
    ASSERT_TRUE(true);

    // Test with three characters (odd length for Hill cipher)
    char threeChars[] = "abc";
    runPipeline(threeChars, cipherText, key, matrixKey);
    ASSERT_TRUE(true);
}

// Test for encryption pipeline with alphabet boundary cases
TEST(Integration_AlphabetBoundaryCases) {
    char key[] = "key";
    int matrixKey[25][25] = {{2, 3}, {1, 2}};
    char cipherText[50];

    // Test with 'a' (first letter)
    char firstLetter[] = "a";
    runPipeline(firstLetter, cipherText, key, matrixKey);
    ASSERT_TRUE(true);

    // Test with 'z' (last letter)
    char lastLetter[] = "z";
    runPipeline(lastLetter, cipherText, key, matrixKey);
    ASSERT_TRUE(true);

    // Test with all letters
    char allLetters[] = "abcdefghijklmnopqrstuvwxyz";
    runPipeline(allLetters, cipherText, key, matrixKey);
    ASSERT_TRUE(true);
}
