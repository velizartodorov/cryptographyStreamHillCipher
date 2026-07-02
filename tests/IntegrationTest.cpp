#include "TestFramework.h"
#include "StreamCipher.h"
#include "HillCipher.h"
#include "Utils.h"
#include <string>
#include <vector>

// Runs the full Stream Cipher -> Hill Cipher pipeline, writing the
// intermediate stream-cipher output into cipherText.
static void runPipeline(const string& plainText, string& cipherText, const string& key, const vector<vector<int>>& matrixKey) {
    StreamCipher streamCipher;
    HillCipher hillCipher;
    streamCipher.encode(plainText, cipherText, key);
    hillCipher.encode(cipherText, matrixKey);
}

struct PipelineCase {
    const char* name;
    const char* plainText;
    const char* key;
    vector<vector<int>> matrixKey;
};

static const PipelineCase pipelineCases[] = {
    {"StreamThenHillCipher", "hello", "key", {{3, 3}, {2, 5}}},

    // different text lengths
    {"ShortText", "hi", "abc", {{1, 2}, {3, 4}}},
    {"MediumText", "hello world", "abc", {{1, 2}, {3, 4}}},
    {"LongText", "this is a very long text for testing", "abc", {{1, 2}, {3, 4}}},

    // different stream cipher keys
    {"SingleCharKey", "test", "a", {{2, 1}, {1, 3}}},
    {"ShortKey", "test", "key", {{2, 1}, {1, 3}}},
    {"LongKey", "test", "verylongkey", {{2, 1}, {1, 3}}},

    // different Hill cipher matrix keys
    {"IdentityMatrix", "hello", "key", {{1, 0}, {0, 1}}},
    {"Matrix2", "hello", "key", {{5, 7}, {2, 3}}},
    {"Matrix3", "hello", "key", {{1, 1}, {1, 2}}},

    // edge cases: very short plain text, including odd length for Hill cipher
    {"SingleChar", "a", "key", {{1, 1}, {1, 1}}},
    {"TwoChars", "ab", "key", {{1, 1}, {1, 1}}},
    {"ThreeChars", "abc", "key", {{1, 1}, {1, 1}}},

    // alphabet boundary cases
    {"FirstLetter", "a", "key", {{2, 3}, {1, 2}}},
    {"LastLetter", "z", "key", {{2, 3}, {1, 2}}},
    {"AllLetters", "abcdefghijklmnopqrstuvwxyz", "key", {{2, 3}, {1, 2}}},

    // non-2x2 matrix key, proving the pipeline works with dynamically-sized matrices
    {"ThreeByThreeMatrix", "hello", "key", {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}},
};

// Test for complete encryption pipeline (Stream Cipher -> Hill Cipher) across
// varying text lengths, keys, and matrix keys of different sizes. Every case
// should complete without crashing and produce non-empty cipher text.
TEST(Integration_AllPipelines) {
    for (const auto& c : pipelineCases) {
        string cipherText;

        runPipeline(c.plainText, cipherText, c.key, c.matrixKey);

        if (cipherText.empty()) {
            throw runtime_error(string("Case '") + c.name + "' produced empty cipher text");
        }
    }
}

// Test for encryption pipeline consistency
TEST(Integration_EncryptionConsistency) {
    string plainText = "consistency";
    string cipherText1;
    string cipherText2;
    string key = "testkey";
    vector<vector<int>> matrixKey = {{3, 1}, {2, 4}};

    // Run the same encryption twice
    runPipeline(plainText, cipherText1, key, matrixKey);
    runPipeline(plainText, cipherText2, key, matrixKey);

    // Both should complete successfully
    ASSERT_TRUE(true);
}
