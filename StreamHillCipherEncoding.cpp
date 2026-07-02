#include "Utils.h"
#include "StreamCipher.h"
#include "HillCipher.h"
#include "Matrix.h"
#include <string>

int main()
{
	string charKey, plainText, cipherText;
	Matrix matrixKey;

	StreamCipher streamCipher;
	HillCipher hillCipher;
	Utils::validateInput(charKey, plainText, matrixKey);
	streamCipher.encode(plainText, cipherText, charKey);
	hillCipher.encode(cipherText, matrixKey);

	system("pause"); // .monitor pause
}