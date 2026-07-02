#include "TestFramework.h"
#include "Utils.h"
#include "Matrix.h"
#include <string>
#include <vector>

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
    Matrix matrix = {{1, 2}, {3, 4}};

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
    {"EmptyString", "", false}, // Empty string is rejected so validateInput can't be tricked into an empty key
};

// Test for Utils::isLowercaseOnly across representative inputs.
TEST(Utils_IsLowercaseOnly_AllCases) {
    for (const auto& c : lowercaseCheckCases) {
        bool result = Utils::isLowercaseOnly(c.text);
        if (result != c.expected) {
            throw runtime_error(string("Case '") + c.name + "': expected " +
                (c.expected ? "true" : "false") + " but got " + (result ? "true" : "false"));
        }
    }
}
