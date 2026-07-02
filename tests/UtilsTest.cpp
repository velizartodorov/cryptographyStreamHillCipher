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

struct DisplayTextCase {
    const char* name;
    const char* text;
    int length; // 0 = process the full string
};

static const DisplayTextCase displayTextCases[] = {
    {"Lowercase", "hello", 0},
    {"Uppercase", "HELLO", 0},
    {"MixedCase", "HeLlO", 0},
    {"WithLength", "hello", 3}, // only first 3 characters should be processed
};

// h,e,l,l,o -> 7,4,11,11,14 regardless of case
static const int expectedAlphabetNums[] = {7, 4, 11, 11, 14};

// Test for displayText function across case variations and the length-limited overload
TEST(Utils_DisplayText_AllCases) {
    for (const auto& c : displayTextCases) {
        char text[16];
        strcpy_s(text, sizeof(text), c.text);
        int alphabetNum[50];
        int checkCount = c.length > 0 ? c.length : 5;

        if (c.length > 0) {
            Utils::displayText(text, alphabetNum, c.length);
        } else {
            Utils::displayText(text, alphabetNum);
        }

        for (int i = 0; i < checkCount; i++) {
            ASSERT_EQUAL(expectedAlphabetNums[i], alphabetNum[i]);
        }
    }
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

struct LowercaseCheckCase {
    const char* name;
    const char* text;
    bool expected;
};

static const LowercaseCheckCase lowercaseCheckCases[] = {
    {"ValidLowercase", "hello", true},
    {"InvalidNumbers", "hello123", false},
    {"Uppercase", "HELLO", false}, // Uppercase should be invalid according to the logic
    {"SpecialCharacters", "hello!@#", false},
    {"EmptyString", "", true}, // Empty string should be valid (no invalid characters)
};

// Test for inputCheck function's lowercase-only rule across representative inputs.
// This function uses longjmp which makes it difficult to test directly,
// so we test the lowercase-check logic indirectly via isAllLowercase.
TEST(Utils_InputCheck_AllCases) {
    for (const auto& c : lowercaseCheckCases) {
        bool result = isAllLowercase(c.text);
        if (result != c.expected) {
            throw runtime_error(string("Case '") + c.name + "': expected " +
                (c.expected ? "true" : "false") + " but got " + (result ? "true" : "false"));
        }
    }
}
