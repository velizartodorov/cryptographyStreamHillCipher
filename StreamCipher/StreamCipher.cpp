#include "StreamCipher.h"
#include "Utils.h"
#include <vector>

void StreamCipher::encode(const string& plainText, string& cipherText, const string& charKey)
{
	int keyLength = static_cast<int>(charKey.length());
	int plainLength = static_cast<int>(plainText.length());
	int j = 0, i = 0;
	vector<int> alphabetNum;

	cout << endl << " --- Stream Cipher --- " << endl;

	cout << endl << " Key: " << endl;
	Utils::displayText(charKey, alphabetNum);

	Utils::displayNumber(alphabetNum);

	cout << endl << " Plain text: " << endl;
	Utils::displayText(plainText, alphabetNum);

	Utils::displayNumber(alphabetNum);

	cout << endl;

	vector<int> tempKey(keyLength);
	for (i = 0; i < keyLength; i++)
	{
		tempKey[i] = charKey[i] - 97;
		cout << " " << tempKey[i];
	}

	cipherText.resize(plainLength);

	for (i = 0; i < plainLength; i++)
	{
		cipherText[i] = ((plainText[i] - 97) + tempKey[j]) % 26;
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

	cout << endl << endl;

	for (i = 0; i < plainLength; i++)
	{
		cout << " " << (int)cipherText[i];
	}

	cout << endl << endl << " Ciphrotext:" << endl << endl;

	for (i = 0; i < plainLength; i++)
	{
		cipherText[i] = cipherText[i] + 65;
		cout << ' ' << cipherText[i];
	}
	cout << endl;
}
