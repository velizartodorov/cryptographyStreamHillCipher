#include "Utils.h"
#include "StreamCipher.h"
#include "HillCipher.h"
#include "Matrix.h"
#include <exception>
#include <string>

int main()
{
	string charKey, plainText, cipherText;
	Matrix matrixKey;

	StreamCipher streamCipher;
	HillCipher hillCipher;

	try
	{
		Utils::validateInput(charKey, plainText, matrixKey);
		streamCipher.encode(plainText, cipherText, charKey);
		hillCipher.encode(cipherText, matrixKey);
	}
	catch (const exception& e)
	{
		cout << endl << " Error: " << e.what() << endl;
		Utils::pauseConsole();
		return 1;
	}

	Utils::pauseConsole();
}