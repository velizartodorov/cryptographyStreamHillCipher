#include "Utils.h"
#include "StreamCipher.h"
#include "HillCipher.h"
#include "Matrix.h"
#include <string>

int main()
{
	string char_key, plain_text, cipher_text;
	Matrix matrix_key;

	StreamCipher streamcipher;
	HillCipher hillcipher;
	Utils::validateInput(char_key, plain_text, matrix_key);
	streamcipher.encode(plain_text, cipher_text, char_key);
	hillcipher.encode(cipher_text, matrix_key);

	system("pause"); // .monitor pause
}