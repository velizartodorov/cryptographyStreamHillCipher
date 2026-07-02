#include "Utils.h"
#include "StreamCipher.h"
#include "HillCipher.h"
#include <string>
#include <vector>

int main()
{
	string char_key, plain_text, cipher_text;
	vector<vector<int>> matrix_key;

	StreamCipher streamcipher;
	HillCipher hillcipher;
	Utils::validateInput(char_key, plain_text, matrix_key);
	streamcipher.encode(plain_text, cipher_text, char_key);
	hillcipher.encode(cipher_text, matrix_key);

	system("pause"); // .monitor pause
}