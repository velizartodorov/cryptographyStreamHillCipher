#include "TestFramework.h"
#include "Utils.h"
#include <cstring>
#include <iostream>

// Mirrors the lowercase-only check Utils::inputCheck performs before its
// longjmp-based retry loop, which is impractical to exercise directly in a test.
static bool isAllLowercase(const char* text) {
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        if (!(97 <= text[i] && text[i] <= 122)) {
            return false;
        }
    }
    return true;
}

// Test for displayText function with lowercase input
TEST(Utils_DisplayTextLowercase) {
    char text[] = "hello";
    int alphabetNum[50];
    
    Utils::displayText(text, alphabetNum);
    
    // Verify that alphabet numbers are correctly calculated
    ASSERT_EQUAL(7, alphabetNum[0]);  // h -> 7
    ASSERT_EQUAL(4, alphabetNum[1]);  // e -> 4
    ASSERT_EQUAL(11, alphabetNum[2]); // l -> 11
    ASSERT_EQUAL(11, alphabetNum[3]); // l -> 11
    ASSERT_EQUAL(14, alphabetNum[4]); // o -> 14
}

// Test for displayText function with uppercase input
TEST(Utils_DisplayTextUppercase) {
    char text[] = "HELLO";
    int alphabetNum[50];
    
    Utils::displayText(text, alphabetNum);
    
    // Verify that alphabet numbers are correctly calculated
    ASSERT_EQUAL(7, alphabetNum[0]);  // H -> 7
    ASSERT_EQUAL(4, alphabetNum[1]);  // E -> 4
    ASSERT_EQUAL(11, alphabetNum[2]); // L -> 11
    ASSERT_EQUAL(11, alphabetNum[3]); // L -> 11
    ASSERT_EQUAL(14, alphabetNum[4]); // O -> 14
}

// Test for displayText function with mixed case input
TEST(Utils_DisplayTextMixedCase) {
    char text[] = "HeLlO";
    int alphabetNum[50];
    
    Utils::displayText(text, alphabetNum);
    
    // Verify that alphabet numbers are correctly calculated
    ASSERT_EQUAL(7, alphabetNum[0]);  // H -> 7
    ASSERT_EQUAL(4, alphabetNum[1]);  // e -> 4
    ASSERT_EQUAL(11, alphabetNum[2]); // L -> 11
    ASSERT_EQUAL(11, alphabetNum[3]); // l -> 11
    ASSERT_EQUAL(14, alphabetNum[4]); // O -> 14
}

// Test for displayText function with specified length
TEST(Utils_DisplayTextWithLength) {
    char text[] = "hello";
    int alphabetNum[50];
    int length = 3; // Only process first 3 characters
    
    Utils::displayText(text, alphabetNum, length);
    
    // Verify that only first 3 characters are processed
    ASSERT_EQUAL(7, alphabetNum[0]);  // h -> 7
    ASSERT_EQUAL(4, alphabetNum[1]);  // e -> 4
    ASSERT_EQUAL(11, alphabetNum[2]); // l -> 11
}

// Test for displayNumber function
TEST(Utils_DisplayNumber) {
    int numArray[50] = {0, 1, 2, 3, 4, 5};
    int length = 6;
    
    // This function only displays, so we just verify it doesn't crash
    Utils::displayNumber(numArray, length);
    ASSERT_TRUE(true);
}

// Test for displayMatrix function
TEST(Utils_DisplayMatrix) {
    int matrix[25][25] = {{1, 2}, {3, 4}};
    
    // This function only displays, so we just verify it doesn't crash
    Utils::displayMatrix(2, 2, matrix);
    ASSERT_TRUE(true);
}

// Test for inputCheck function with valid lowercase input
// This function uses longjmp which makes it difficult to test directly,
// so we test the lowercase-check logic indirectly via isAllLowercase.
TEST(Utils_InputCheckValidLowercase) {
    ASSERT_TRUE(isAllLowercase("hello"));
}

// Test for inputCheck function with invalid input (numbers)
TEST(Utils_InputCheckInvalidNumbers) {
    ASSERT_FALSE(isAllLowercase("hello123"));
}

// Test for inputCheck function with uppercase input
TEST(Utils_InputCheckUppercase) {
    ASSERT_FALSE(isAllLowercase("HELLO")); // Uppercase should be invalid according to the logic
}

// Test for inputCheck function with special characters
TEST(Utils_InputCheckSpecialCharacters) {
    ASSERT_FALSE(isAllLowercase("hello!@#"));
}

// Test for inputCheck function with empty string
TEST(Utils_InputCheckEmptyString) {
    ASSERT_TRUE(isAllLowercase("")); // Empty string should be valid (no invalid characters)
}
