#include "StreamCipher.h"
#include "Utils.h"
#include <stdexcept>
#include <vector>

namespace {
    // Prints the alphabet-number breakdown of the key and plain text.
    void displayKeyAndPlainText(const string& charKey, const string& plainText) {
        vector<int> alphabetNum;

        cout << endl << " Key: " << endl;
        Utils::displayText(charKey, alphabetNum);
        Utils::displayNumber(alphabetNum);

        cout << endl << " Plain text: " << endl;
        Utils::displayText(plainText, alphabetNum);
        Utils::displayNumber(alphabetNum);
    }

    // Converts charKey into its initial 0-25 keystream and prints it.
    vector<int> buildInitialKeyStream(const string& charKey) {
        cout << endl;
        vector<int> tempKey(charKey.length());
        for (size_t i = 0; i < charKey.length(); i++)
        {
            tempKey[i] = charKey[i] - 'a';
            cout << " " << tempKey[i];
        }
        return tempKey;
    }

    // Substitutes plainText against the keystream (which cycles into the
    // ciphertext it has already produced once exhausted), producing
    // cipherText as raw 0-25 values, not yet converted to letters.
    string substitute(const string& plainText, vector<int> tempKey) {
        int keyLength = static_cast<int>(tempKey.size());
        int plainLength = static_cast<int>(plainText.length());

        string cipherText;
        cipherText.resize(plainLength);

        int j = 0;
        for (int i = 0; i < plainLength; i++)
        {
            cipherText[i] = ((plainText[i] - 'a') + tempKey[j]) % 26;
            j++;
            if (j == keyLength)
            {
                j = 0;
                for (int m = i - (keyLength - 1); m < i + 1; m++)
                {
                    tempKey[j] = cipherText[m];
                    j++;
                }
                j = 0;
            }
        }
        return cipherText;
    }

    // Prints the raw 0-25 numeric form of cipherText.
    void printRawCipherNumbers(const string& cipherText) {
        cout << endl << endl;
        for (unsigned char c : cipherText)
        {
            cout << " " << (int)c;
        }
    }

    // Converts cipherText in place from raw 0-25 values to uppercase letters,
    // printing each as it is converted.
    void printAndConvertToLetters(string& cipherText) {
        cout << endl << endl << " Ciphrotext:" << endl << endl;
        for (size_t i = 0; i < cipherText.length(); i++)
        {
            cipherText[i] = Utils::numberToLetter(static_cast<unsigned char>(cipherText[i]));
            cout << ' ' << cipherText[i];
        }
        cout << endl;
    }
}

void StreamCipher::encode(const string& plainText, string& cipherText, const string& charKey)
{
	if (charKey.empty())
	{
		throw invalid_argument("StreamCipher::encode: charKey must not be empty");
	}

	cout << endl << " --- Stream Cipher --- " << endl;

	displayKeyAndPlainText(charKey, plainText);

	vector<int> tempKey = buildInitialKeyStream(charKey);

	cipherText = substitute(plainText, tempKey);

	printRawCipherNumbers(cipherText);
	printAndConvertToLetters(cipherText);
}
