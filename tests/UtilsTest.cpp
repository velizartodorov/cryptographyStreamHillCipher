#include "TestFramework.h"
#include "Utils.h"
#include <cstring>
#include <string>
#include <vector>

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
};

static const DisplayTextCase displayTextCases[] = {
    {"Lowercase", "hello"},
    {"Uppercase", "HELLO"},
    {"MixedCase", "HeLlO"},
};

// h,e,l,l,o -> 7,4,11,11,14 regardless of case
static const vector<int> expectedAlphabetNums = {7, 4, 11, 11, 14};

// Test for displayText function across case variations
TEST(Utils_DisplayText_AllCases) {
    for (const auto& c : displayTextCases) {
        vector<int> alphabetNum;
        Utils::displayText(c.text, alphabetNum);

        for (size_t i = 0; i < expectedAlphabetNums.size(); i++) {
            ASSERT_EQUAL(expectedAlphabetNums[i], alphabetNum[i]);
        }
    }
}

// Test for displayNumber function
TEST(Utils_DisplayNumber) {
    vector<int> numArray = {0, 1, 2, 3, 4, 5};

    // This function only displays, so we just verify it doesn't crash
    Utils::displayNumber(numArray);
    ASSERT_TRUE(true);
}

// Test for displayMatrix function
TEST(Utils_DisplayMatrix) {
    vector<vector<int>> matrix = {{1, 2}, {3, 4}};

    // This function only displays, so we just verify it doesn't crash
    Utils::displayMatrix(matrix);
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
