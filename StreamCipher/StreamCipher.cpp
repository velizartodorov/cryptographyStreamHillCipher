#include "StreamCipher.h"
#include "Utils.h"
#include <vector>

void StreamCipher::encode(const string& plain_text, string& cipher_text, const string& char_key)
{
	int key_length = static_cast<int>(char_key.length());
	int plain_length = static_cast<int>(plain_text.length());
	int j = 0, i = 0;
	vector<int> alphabet_num;

	cout << endl << " --- Stream Cipher --- " << endl;

	cout << endl << " Key: " << endl;
	Utils::displayText(char_key, alphabet_num);

	Utils::displayNumber(alphabet_num);

	cout << endl << " Plain text: " << endl;
	Utils::displayText(plain_text, alphabet_num);

	Utils::displayNumber(alphabet_num);

	cout << endl;

	vector<int> temp_key(key_length);
	for (i = 0; i < key_length; i++)
	{
		temp_key[i] = char_key[i] - 97;
		cout << " " << temp_key[i];
	}

	cipher_text.resize(plain_length);

	for (i = 0; i < plain_length; i++)
	{
		cipher_text[i] = ((plain_text[i] - 97) + temp_key[j]) % 26;
		j++;
		if (j == key_length)
		{
			j = 0;
			for (int m = i - (key_length - 1); m < i + 1; m++)
			{
				temp_key[j] = cipher_text[m];
				j++;
			}
			j = 0;
		}
	}

	cout << endl << endl;

	for (i = 0; i < plain_length; i++)
	{
		cout << " " << (int)cipher_text[i];
	}

	cout << endl << endl << " Ciphrotext:" << endl << endl;

	for (i = 0; i < plain_length; i++)
	{
		cipher_text[i] = cipher_text[i] + 65;
		cout << ' ' << cipher_text[i];
	}
	cout << endl;
}
