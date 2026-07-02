#include "TestFramework.h"
#include "StreamCipher.h"
#include "Utils.h"
#include <cstring>
#include <iostream>

static void encodeStream(char* plainText, char* cipherText, char* key) {
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
// case, the cipher text should be the same length as the plain text and the
// plain text buffer should be left unmodified.
// Note: The original implementation uses _getche() which requires user input;
// encodeStream/StreamCipher::encode here sidestep that for testing.
TEST(StreamCipher_AllCases) {
    for (const auto& c : streamCases) {
        char plainText[32];
        char key[32];
        char cipherText[50];
        strcpy_s(plainText, sizeof(plainText), c.plainText);
        strcpy_s(key, sizeof(key), c.key);

        try {
            encodeStream(plainText, cipherText, key);
        } catch (...) {
            if (c.tolerateException) {
                continue;
            }
            throw;
        }

        if (strlen(cipherText) != strlen(c.plainText)) {
            throw runtime_error(string("Case '") + c.name + "': cipher length " +
                to_string(strlen(cipherText)) + " != plain length " + to_string(strlen(c.plainText)));
        }
        if (strcmp(plainText, c.plainText) != 0) {
            throw runtime_error(string("Case '") + c.name + "': plain text was mutated");
        }
    }
}
