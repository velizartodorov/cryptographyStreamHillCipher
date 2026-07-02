#include "HillCipher.h"
#include "Utils.h"
#include <cctype>
#include <stdexcept>

namespace {
    // Validates matrixKey is non-empty and square, returning its size n.
    int validateSquareMatrix(const Matrix& matrixKey) {
        int n = static_cast<int>(matrixKey.size());
        if (n <= 0)
        {
            throw invalid_argument("HillCipher::encode: matrixKey must be non-empty");
        }
        for (const auto& row : matrixKey)
        {
            if (static_cast<int>(row.size()) != n)
            {
                throw invalid_argument("HillCipher::encode: matrixKey must be square");
            }
        }
        return n;
    }

    // Pads plainTxt in place with 'x'/'X' so its length becomes a multiple of n.
    void padToBlockSize(string& plainTxt, int n) {
        int strLength = static_cast<int>(plainTxt.length());
        int remainder = strLength % n;

        if (remainder != 0)
        {
            int padCount = n - remainder;
            cout << endl << " Length of plain text is " << strLength << " symbols, not a multiple of " << n << "!";

            char padChar = islower(static_cast<unsigned char>(plainTxt[0])) ? 'x' : 'X';
            plainTxt.append(padCount, padChar);

            cout << " Corrected plain text:" << endl;
        }
        else
        {
            cout << endl << " Length of plain text is correct." << endl;
        }
    }

    // Converts (already padded) plainTxt into its row-major alphabet-number
    // matrix (rowCount x n), displaying each step along the way.
    Matrix buildAlphabetMatrix(const string& plainTxt, int n) {
        vector<int> alphabetNum;
        Utils::displayText(plainTxt, alphabetNum);
        Utils::displayNumber(alphabetNum);

        int rowCount = static_cast<int>(plainTxt.length()) / n;
        cout << endl << " Row count of plain text matrix: " << rowCount << endl;

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
        return alphabetMatrix;
    }

    // Multiplies alphabetMatrix (rowCount x n) by matrixKey (n x n).
    Matrix multiplyByKey(const Matrix& alphabetMatrix, const Matrix& matrixKey) {
        int rowCount = static_cast<int>(alphabetMatrix.size());
        int n = static_cast<int>(matrixKey.size());

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
        return resultMatrix;
    }

    // Prints the final encrypted ciphertext letters.
    void printCiphertext(const string& plainTxt, const Matrix& resultMatrix) {
        cout << endl << " Encrypted equivalent of '" << plainTxt << "' is: " << endl << endl;
        for (const auto& row : resultMatrix)
        {
            for (int value : row)
            {
                cout << " " << Utils::numberToLetter(value);
            }
        }
        cout << endl << endl;
    }
}

void HillCipher::encode(string& plainTxt, const Matrix& matrixKey)
{
	int n = validateSquareMatrix(matrixKey); // block size: matrixKey is n x n

	cout << endl << " --- Hill cipher --- " << endl;

	cout << endl << " Key Matrix: ";
	Utils::displayMatrix(matrixKey);

	padToBlockSize(plainTxt, n);

	Matrix alphabetMatrix = buildAlphabetMatrix(plainTxt, n);
	Matrix resultMatrix = multiplyByKey(alphabetMatrix, matrixKey);

	printCiphertext(plainTxt, resultMatrix);
}
