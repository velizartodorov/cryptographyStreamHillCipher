#include "StreamCipher.h"	
#include "Utils.h"

void StreamCipher::encode(char* plain_text, char* cipher_text, char* char_key)
{
	int key_length = strlen(char_key);
	int plain_length = strlen(plain_text);
	int j = 0, i = 0, alphabet_num[50];
	char temp_key[64];

	cout << endl << " --- Stream Cipher --- " << endl;

	cout << endl << " Key: " << endl;
	Utils::displayText(char_key, alphabet_num, key_length);

	_getche();

	Utils::displayNumber(alphabet_num, key_length);

	_getche();

	cout << endl << " Plain text: " << endl;
	Utils::displayText(plain_text, alphabet_num, plain_length);

	_getche();

	Utils::displayNumber(alphabet_num, plain_length);

	_getche();

	cout << endl;

	strcpy_s(temp_key, char_key);
	for (i = 0; i < key_length; i++)
	{
		temp_key[i] = temp_key[i] - 97;
		cout << " " << (int)temp_key[i];
	}

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

	_getche();

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
	cipher_text[i] = '\0';
	cout << endl;
}