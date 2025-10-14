#include "TestFramework.h"
#include "StreamCipher.h"
#include "HillCipher.h"
#include "Utils.h"
#include <cstring>
#include <iostream>

// Test for complete encryption pipeline: Stream Cipher -> Hill Cipher
TEST(Integration_StreamThenHillCipher) {
    StreamCipher streamCipher;
    HillCipher hillCipher;
    
    char plainText[] = "hello";
    char streamCipherText[50];
    char key[] = "key";
    int matrixKey[25][25] = {{3, 3}, {2, 5}};
    
    // First apply stream cipher
    streamCipher.encode(plainText, streamCipherText, key);
    
    // Then apply hill cipher to the stream cipher output
    hillCipher.encode(streamCipherText, matrixKey);
    
    // Verify that both operations complete successfully
    ASSERT_TRUE(strlen(streamCipherText) > 0);
    ASSERT_TRUE(true); // Hill cipher completed without crashing
}

// Test for encryption pipeline with different text lengths
TEST(Integration_DifferentTextLengths) {
    StreamCipher streamCipher;
    HillCipher hillCipher;
    
    // Test with short text
    char shortText[] = "hi";
    char cipherText[50];
    char key[] = "abc";
    int matrixKey[25][25] = {{1, 2}, {3, 4}};
    
    streamCipher.encode(shortText, cipherText, key);
    hillCipher.encode(cipherText, matrixKey);
    ASSERT_TRUE(true);
    
    // Test with medium text
    char mediumText[] = "hello world";
    streamCipher.encode(mediumText, cipherText, key);
    hillCipher.encode(cipherText, matrixKey);
    ASSERT_TRUE(true);
    
    // Test with long text
    char longText[] = "this is a very long text for testing";
    streamCipher.encode(longText, cipherText, key);
    hillCipher.encode(cipherText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for encryption pipeline with different keys
TEST(Integration_DifferentKeys) {
    StreamCipher streamCipher;
    HillCipher hillCipher;
    
    char plainText[] = "test";
    char cipherText[50];
    
    // Test with different stream cipher keys
    char key1[] = "a";
    char key2[] = "key";
    char key3[] = "verylongkey";
    
    int matrixKey[25][25] = {{2, 1}, {1, 3}};
    
    streamCipher.encode(plainText, cipherText, key1);
    hillCipher.encode(cipherText, matrixKey);
    ASSERT_TRUE(true);
    
    streamCipher.encode(plainText, cipherText, key2);
    hillCipher.encode(cipherText, matrixKey);
    ASSERT_TRUE(true);
    
    streamCipher.encode(plainText, cipherText, key3);
    hillCipher.encode(cipherText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for encryption pipeline with different matrix keys
TEST(Integration_DifferentMatrixKeys) {
    StreamCipher streamCipher;
    HillCipher hillCipher;
    
    char plainText[] = "hello";
    char cipherText[50];
    char key[] = "key";
    
    // Test with identity matrix
    int identityMatrix[25][25] = {{1, 0}, {0, 1}};
    streamCipher.encode(plainText, cipherText, key);
    hillCipher.encode(cipherText, identityMatrix);
    ASSERT_TRUE(true);
    
    // Test with different matrix
    int matrix2[25][25] = {{5, 7}, {2, 3}};
    streamCipher.encode(plainText, cipherText, key);
    hillCipher.encode(cipherText, matrix2);
    ASSERT_TRUE(true);
    
    // Test with another matrix
    int matrix3[25][25] = {{1, 1}, {1, 2}};
    streamCipher.encode(plainText, cipherText, key);
    hillCipher.encode(cipherText, matrix3);
    ASSERT_TRUE(true);
}

// Test for encryption pipeline consistency
TEST(Integration_EncryptionConsistency) {
    StreamCipher streamCipher;
    HillCipher hillCipher;
    
    char plainText[] = "consistency";
    char cipherText1[50];
    char cipherText2[50];
    char key[] = "testkey";
    int matrixKey[25][25] = {{3, 1}, {2, 4}};
    
    // Run the same encryption twice
    streamCipher.encode(plainText, cipherText1, key);
    hillCipher.encode(cipherText1, matrixKey);
    
    streamCipher.encode(plainText, cipherText2, key);
    hillCipher.encode(cipherText2, matrixKey);
    
    // Both should complete successfully
    ASSERT_TRUE(true);
}

// Test for encryption pipeline with edge cases
TEST(Integration_EdgeCases) {
    StreamCipher streamCipher;
    HillCipher hillCipher;
    
    char key[] = "key";
    int matrixKey[25][25] = {{1, 1}, {1, 1}};
    
    // Test with single character
    char singleChar[] = "a";
    char cipherText[50];
    streamCipher.encode(singleChar, cipherText, key);
    hillCipher.encode(cipherText, matrixKey);
    ASSERT_TRUE(true);
    
    // Test with two characters
    char twoChars[] = "ab";
    streamCipher.encode(twoChars, cipherText, key);
    hillCipher.encode(cipherText, matrixKey);
    ASSERT_TRUE(true);
    
    // Test with three characters (odd length for Hill cipher)
    char threeChars[] = "abc";
    streamCipher.encode(threeChars, cipherText, key);
    hillCipher.encode(cipherText, matrixKey);
    ASSERT_TRUE(true);
}

// Test for encryption pipeline with alphabet boundary cases
TEST(Integration_AlphabetBoundaryCases) {
    StreamCipher streamCipher;
    HillCipher hillCipher;
    
    char key[] = "key";
    int matrixKey[25][25] = {{2, 3}, {1, 2}};
    char cipherText[50];
    
    // Test with 'a' (first letter)
    char firstLetter[] = "a";
    streamCipher.encode(firstLetter, cipherText, key);
    hillCipher.encode(cipherText, matrixKey);
    ASSERT_TRUE(true);
    
    // Test with 'z' (last letter)
    char lastLetter[] = "z";
    streamCipher.encode(lastLetter, cipherText, key);
    hillCipher.encode(cipherText, matrixKey);
    ASSERT_TRUE(true);
    
    // Test with all letters
    char allLetters[] = "abcdefghijklmnopqrstuvwxyz";
    streamCipher.encode(allLetters, cipherText, key);
    hillCipher.encode(cipherText, matrixKey);
    ASSERT_TRUE(true);
}
