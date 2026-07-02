#include "HillCipher.h"
#include "Utils.h"

jmp_buf resumeHere;

void HillCipher::encode(string& plainTxt, const Matrix& matrixKey)
{
	int n = static_cast<int>(matrixKey.size()); // block size: matrixKey is n x n

	if (setjmp(resumeHere) != 0)
	{
		cout << "" << endl;
	}

	cout << endl << " --- Hill cipher --- " << endl;

	// Padding plainTxt so its length is a multiple of n

	int strLength = static_cast<int>(plainTxt.length());
	int remainder = strLength % n;

	if (remainder != 0)
	{
		int padCount = n - remainder;
		cout << endl << " Length of plain text is " << strLength << " symbols, not a multiple of " << n << "!";

		char padChar = (97 <= plainTxt[0] && plainTxt[0] <= 122) ? 'x' : 'X';
		plainTxt.append(padCount, padChar);

		cout << " Corrected plain text:" << endl;
		vector<int> paddedAlphabetNum;
		Utils::displayText(plainTxt, paddedAlphabetNum);
	}
	else
	{
		cout << endl << " Length of plain text is correct." << endl;
	}

	cout << endl << " Key Matrix: ";
	Utils::displayMatrix(matrixKey);

	vector<int> alphabetNum;
	Utils::displayText(plainTxt, alphabetNum);
	Utils::displayNumber(alphabetNum);

	// Calculating rows of alphabetMatrix

	strLength = static_cast<int>(plainTxt.length());
	int rowCount = strLength / n;
	cout << endl << " Row count of plain text matrix: " << rowCount << endl;

	// Transforming values of alphabetNum into 2D

	Matrix alphabetMatrix(rowCount, n);
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < n; j++)
		{
			alphabetMatrix[i][j] = alphabetNum[i * n + j];
		}
	}

	cout << endl << " Matrix of plain text:";
	Utils::displayMatrix(alphabetMatrix);

	// Multiplying and visualizing key matrix with matrix of text;

	Matrix resultMatrix(rowCount, n);
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				resultMatrix[i][j] += (alphabetMatrix[i][k] * matrixKey[k][j]);
			}
		}
	}

	cout << endl << " Calculated matrix: ";
	Utils::displayMatrix(resultMatrix);

	cout << endl << " Encrypted equivalent of '" << plainTxt << "' is: " << endl << endl;
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << " " << (char)((resultMatrix[i][j]) % 26 + 65);
		}
	}
	cout << endl << endl;

}
