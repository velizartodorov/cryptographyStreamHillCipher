#include "HillCipher.h"
#include "Utils.h"

using namespace std;

jmp_buf resume_here;

void HillCipher::encode(char* plain_txt, int matrix_key[25][25])
{
	int row_count, i, j, k, str_length, alphabet_num[50], alphabet_matrix[25][25], result_matrix[25][25];

	if (setjmp(resume_here) != 0)
	{
		cout << "" << endl;
	}

	cout << endl << " --- Hill cipher --- " << endl;

	// Modding plain_text

	str_length = strlen(plain_txt);

	if (str_length % 2 != 0)
	{
		cout << endl << " Length of plain text is odd number - " << str_length << " symbols!";

		if (97 <= plain_txt[0] && plain_txt[0] <= 122)
		{
			plain_txt[str_length] = 'x';
		}
		else if (65 <= plain_txt[0] && plain_txt[0] <= 90)
		{
			plain_txt[str_length] = 'X';
		}
		plain_txt[str_length + 1] = '\0';
		str_length++;
		cout << " Corrected plain text:" << endl;
		Utils::displayText(plain_txt, alphabet_num, str_length);
	}
	else
	{
		cout << endl << " Length of plain text is correct." << endl;
	}

	_getche();

	cout << endl << " Key Matrix: ";
	Utils::displayMatrix(2, 2, matrix_key);

	_getche();

	Utils::displayText(plain_txt, alphabet_num, str_length);
	Utils::displayNumber(alphabet_num, str_length);

	_getche();

	// Calculating rows of alphabet_matrix

	str_length = strlen(plain_txt);
	row_count = str_length / 2;
	cout << endl << " Row count of plain text matrix: " << row_count << endl;

	//  Transforming values of alphabet_num into 2D

	for (i = 0; i < row_count; i++)
	{
		for (j = 0; j < 2; j++)
		{
			alphabet_matrix[i][j] = alphabet_num[i * 2 + j];
		}
	}

	_getche();

	cout << endl << " Matrix of plain text:";
	Utils::displayMatrix(row_count, 2, alphabet_matrix);

	_getche();

	// Multiplying and visualizing key matrix with matrix of text;

	for (i = 0; i < row_count; i++)
	{
		for (j = 0; j < 2; j++)
		{
			result_matrix[i][j] = 0;
			for (k = 0; k < 2; k++)
			{
				result_matrix[i][j] += (alphabet_matrix[i][k] * matrix_key[k][j]);
			}
		}
	}

	cout << endl << " Calculated matrix: ";
	Utils::displayMatrix(row_count, 2, result_matrix);

	cout << endl << " Encrypted equivalent of '" << plain_txt << "' is: " << endl << endl;
	for (i = 0; i < row_count; ++i)
	{
		for (j = 0; j < 2; ++j)
		{
			cout << " " << (char)((result_matrix[i][j]) % 26 + 65);
		}
	}
	cout << endl << endl;

}
