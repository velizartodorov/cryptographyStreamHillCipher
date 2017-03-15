#include<iostream>      /* cin, cout , system - pause, colour */
#include<ctype.h>	/* toupper */
#include<setjmp.h>      /* setjmp, longjmp */
#include<string.h>      /* strlen, strcpy */
#include<conio.h>	/* _getche(); */

using namespace std;
 
 jmp_buf resume_here; // set_jmp

// Check if proper letters are inputted

void inputCheck(char* text, int str_length)
{
   str_length = strlen(text);
   int i;
   
   for (i = 0; i < str_length; i++)
   {
		if (! (97 <= text[i] && text[i] <= 122) )
        {
			system("CLS");
            cout << endl << " Enter text: (a-z)!" << endl;
            longjmp(resume_here, 1);
        }
   }
}

// Displaying a matrix

 void displayMatrix(int row, int column, int matrix[25][25])
 {
	int i, j;
	cout << endl;
    for ( i = 0; i < row; i++)
    {
		cout << endl;
        for (j = 0; j < column; j++)
        {
			cout << "  " << matrix[i][j];
		}
        cout << endl;
    }
 }

// Diplsay letter position of plain-text

void displayText(char* display_text, int alphabet_num[50], int str_length)
{
	int i;
    str_length = strlen(display_text);

    cout << endl;
    for (i = 0; i < str_length; i++)
    {
        if (97 <= display_text[i] && display_text[i] <= 122)
        {
            alphabet_num[i] = display_text[i] - 97;
            cout << " " << (char) toupper ( display_text[i] );
		}
	   
        else if (65 <= display_text[i] && display_text[i] <= 90)
        {
            alphabet_num[i] = display_text[i] - 65;
            cout << " " << display_text[i];
        }
    } cout << endl;
}

// Displaying cipher equivalent of alphabet

void displayNumber(int num_array[50], int str_length)
{
	int i;
	cout << endl;
	for (i = 0; i < str_length; i++)
		cout  << " " << num_array[i];
	cout << endl;
}

// Stream cipher

void streamCipher(char* plain_text, char* cipher_text, char* char_key)
{
	int key_length = strlen(char_key);
	int plain_length = strlen(plain_text);
	int j = 0, i = 0, alphabet_num[50];
	char temp_key[64];

   cout << endl << " --- Stream Cipher --- " << endl;
   
   cout << endl << " Key: " << endl;
   displayText(char_key, alphabet_num, key_length);

   _getche();

   displayNumber(alphabet_num, key_length);
   
   _getche();

   cout << endl << " Plain text: " << endl;
   displayText(plain_text, alphabet_num, plain_length);

   _getche();

   displayNumber(alphabet_num, plain_length);	

   _getche();
	
	cout << endl;

	strcpy_s(temp_key, char_key);
	for (i = 0; i < key_length; i++)
	{
		temp_key[i] = temp_key[i] - 97;
		cout << " " << (int) temp_key[i];
	}

	for (i = 0; i < plain_length; i++)
	{
		cipher_text[i] = ((plain_text[i] - 97) + temp_key[j]) % 26;
		j ++;
		if (j == key_length)
		{
			j = 0;
			for (int m = i - (key_length - 1); m < i + 1; m++)
			{	
				temp_key[j] = cipher_text[m];
				j ++;
			}
			j = 0;
		}
	}

	_getche();

	cout << endl << endl;

    for (i = 0; i < plain_length; i++)
	{
		 cout << " " << (int) cipher_text[i];
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

// calling Hill cipher

void hillCipher(char* plain_txt, int matrix_key[25][25])
{
   int row_count, i, j, k, str_length, alphabet_num[50], alphabet_matrix[25][25], result_matrix[25][25];

   if (setjmp(resume_here) != 0)
   {cout << "" << endl;}

   cout << endl << " --- Hill cipher --- " << endl;
 
   // Modding plain_text

   str_length = strlen(plain_txt);

    if (str_length % 2 != 0)
    {
        cout << endl << " Length of plain text is odd number - " <<str_length << " symbols!";

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
        cout << " Corrected plain text:" << endl ;
		displayText(plain_txt,alphabet_num, str_length);
    }
    else
    {
        cout << endl << " Length of plain text is correct." << endl;
    }

   	_getche();

   cout << endl << " Key Matrix: ";
   displayMatrix(2, 2, matrix_key);

   	_getche();
   
   displayText(plain_txt,alphabet_num, str_length);
   displayNumber(alphabet_num, str_length);

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
            alphabet_matrix[i][j] = alphabet_num[i*2+j];
        }
    }
   
    _getche();

   cout << endl << " Matrix of plain text:";
   displayMatrix(row_count, 2, alphabet_matrix);

    _getche();

   // Multiplying and visualizing key matrix with matrix of text;

    for (i = 0; i < row_count; i++)
    {
		for (j = 0; j < 2; j++)
		{	
		result_matrix[i][j]=0;
		for (k = 0; k < 2; k++)
			{
				result_matrix[i][j] += (alphabet_matrix[i][k] * matrix_key[k][j]);
			}
		}
	}
  
   cout << endl << " Calculated matrix: ";
   displayMatrix(row_count, 2, result_matrix);

    cout << endl << " Encrypted equivalent of '" << plain_txt << "' is: " << endl << endl;
    for (i = 0; i < row_count; ++i)
    {
        for (j = 0; j < 2; ++j)
        {
            cout << " " <<  (char) ( (result_matrix[i][j]) % 26 + 65 ) ;
        }
    }
     cout << endl << endl;

}

void main()
{
   system("color F0"); // white background, black letters
   char	char_key[50],  plain_text[50], cipher_text[50];
   int i, j, str_length, matrix_key[25][25]; 

   if (setjmp(resume_here) != 0)
   {cout << "" ;}
   cout << endl << " --- Stream and Hill ciphers --- " << endl;
   
   cout << endl <<" Enter plain text: ";
   cin >> plain_text;

   inputCheck(plain_text, str_length);

    if (setjmp(resume_here) != 0)
   {cout << "" ;}

   cout << endl <<" Enter stream key: ";
   cin >> char_key;

   inputCheck(char_key, str_length);

    cout << endl << " Enter Hill key (matrix [2 x 2]):" << endl;

    for (i = 0; i < 2; i++)
    {
	for (j = 0; j < 2; j++)
        {
		cout << endl << " Value [" << i + 1 << "," << j + 1 << "]: ";
		cin >> matrix_key[i][j];
        }
    }

   streamCipher(plain_text, cipher_text, char_key);
   hillCipher(cipher_text, matrix_key);

   system("pause"); // .monitor pause
}
