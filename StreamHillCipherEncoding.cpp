#include "Utils.h"
#include "StreamCipher.h"
#include "HillCipher.h"

int main()
{
	char char_key[50], plain_text[50], cipher_text[50];
	int matrix_key[25][25];

	StreamCipher streamcipher;
	HillCipher hillcipher;
	Utils::validateInput(char_key, plain_text, cipher_text, matrix_key);
	streamcipher.encode(plain_text, cipher_text, char_key);
	hillcipher.encode(cipher_text, matrix_key);

	system("pause"); // .monitor pause
}