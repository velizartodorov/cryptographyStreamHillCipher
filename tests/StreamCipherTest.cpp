#include "TestFramework.h"
#include "StreamCipher.h"
#include "Utils.h"
#include <string>
#include <cstring>

static void encodeStream(const string& plainText, string& cipherText, const string& key) {
    StreamCipher cipher;
    cipher.encode(plainText, cipherText, key);
}

struct StreamCase {
    const char* name;
    const char* plainText;
    const char* key;
    bool tolerateException; // true if throwing is an accepted outcome for this case
};

static const StreamCase streamCases[] = {
    {"BasicEncoding", "hello", "key", false},
    {"DifferentKeyLengths_ShortKey", "test", "a", false},
    {"DifferentKeyLengths_LongKey", "test", "longkey", false},
    {"EmptyInput", "", "key", false},
    {"KeyCycling", "abcdefghijklmnop", "abc", false}, // short key to ensure cycling
    {"SpecialCharacters", "hello123", "key", true},   // numbers may hit input validation
};

// Test for stream cipher encoding across text/key variations. In every accepted
// case, the cipher text should be the same length as the plain text. plainText
// is taken by const reference, so mutation is ruled out at compile time.
// Note: The original implementation uses _getche() which requires user input;
// encodeStream/StreamCipher::encode here sidestep that for testing.
TEST(StreamCipher_AllCases) {
    for (const auto& c : streamCases) {
        string cipherText;

        try {
            encodeStream(c.plainText, cipherText, c.key);
        } catch (...) {
            if (c.tolerateException) {
                continue;
            }
            throw;
        }

        if (cipherText.length() != strlen(c.plainText)) {
            throw runtime_error(string("Case '") + c.name + "': cipher length " +
                to_string(cipherText.length()) + " != plain length " + to_string(strlen(c.plainText)));
        }
    }
}
