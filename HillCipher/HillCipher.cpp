#include "HillCipher.h"
#include "Utils.h"

jmp_buf resume_here;

void HillCipher::encode(string& plain_txt, const Matrix& matrix_key)
{
	int n = static_cast<int>(matrix_key.size()); // block size: matrix_key is n x n

	if (setjmp(resume_here) != 0)
	{
		cout << "" << endl;
	}

	cout << endl << " --- Hill cipher --- " << endl;

	// Padding plain_text so its length is a multiple of n

	int str_length = static_cast<int>(plain_txt.length());
	int remainder = str_length % n;

	if (remainder != 0)
	{
		int pad_count = n - remainder;
		cout << endl << " Length of plain text is " << str_length << " symbols, not a multiple of " << n << "!";

		char pad_char = (97 <= plain_txt[0] && plain_txt[0] <= 122) ? 'x' : 'X';
		plain_txt.append(pad_count, pad_char);

		cout << " Corrected plain text:" << endl;
		vector<int> padded_alphabet_num;
		Utils::displayText(plain_txt, padded_alphabet_num);
	}
	else
	{
		cout << endl << " Length of plain text is correct." << endl;
	}

	cout << endl << " Key Matrix: ";
	Utils::displayMatrix(matrix_key);

	vector<int> alphabet_num;
	Utils::displayText(plain_txt, alphabet_num);
	Utils::displayNumber(alphabet_num);

	// Calculating rows of alphabet_matrix

	str_length = static_cast<int>(plain_txt.length());
	int row_count = str_length / n;
	cout << endl << " Row count of plain text matrix: " << row_count << endl;

	// Transforming values of alphabet_num into 2D

	Matrix alphabet_matrix(row_count, n);
	for (int i = 0; i < row_count; i++)
	{
		for (int j = 0; j < n; j++)
		{
			alphabet_matrix[i][j] = alphabet_num[i * n + j];
		}
	}

	cout << endl << " Matrix of plain text:";
	Utils::displayMatrix(alphabet_matrix);

	// Multiplying and visualizing key matrix with matrix of text;

	Matrix result_matrix(row_count, n);
	for (int i = 0; i < row_count; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				result_matrix[i][j] += (alphabet_matrix[i][k] * matrix_key[k][j]);
			}
		}
	}

	cout << endl << " Calculated matrix: ";
	Utils::displayMatrix(result_matrix);

	cout << endl << " Encrypted equivalent of '" << plain_txt << "' is: " << endl << endl;
	for (int i = 0; i < row_count; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << " " << (char)((result_matrix[i][j]) % 26 + 65);
		}
	}
	cout << endl << endl;

}
