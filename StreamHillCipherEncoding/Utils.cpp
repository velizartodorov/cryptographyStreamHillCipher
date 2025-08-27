#include "Utils.h"

jmp_buf Utils::resume_here;

    void Utils::validateInput(char char_key[50], char plain_text[50], char cipher_text[50], int matrix_key[25][25]) {
        system("color F0"); 
        int i, j, str_length;

        if (setjmp(resume_here) != 0)
        {
            cout << "";
        }
        cout << endl << " --- Stream and Hill ciphers --- " << endl;

        cout << endl << " Enter plain text: ";
        cin >> plain_text;

        inputCheck(plain_text, str_length);

        if (setjmp(resume_here) != 0)
        {
            cout << "";
        }

        cout << endl << " Enter stream key: ";
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
    }

    void Utils::inputCheck(char* text, int str_length)
    {
        str_length = strlen(text);

        int i;

        for (i = 0; i < str_length; i++)
        {
            if (!(97 <= text[i] && text[i] <= 122))
            {
                system("CLS");
                cout << endl << " Enter text: (a-z)!" << endl;
                longjmp(resume_here, 1);
            }
        }
    }

    void Utils::displayMatrix(int row, int column, int matrix[25][25]) {
        cout << "\n";
        for (int i = 0; i < row; ++i) {
            cout << "\n";
            for (int j = 0; j < column; ++j) cout << "  " << matrix[i][j];
            cout << "\n";
        }
    }

    void Utils::displayText(char* display_text, int alphabet_num[50]) {
        int n = strlen(display_text);
        cout << "\n";
        for (int i = 0; i < n; ++i) {
            unsigned char c = static_cast<unsigned char>(display_text[i]);
            if (97 <= c && c <= 122) {
                alphabet_num[i] = c - 97;
                cout << " " << static_cast<char>(toupper(c));
            }
            else if (65 <= c && c <= 90) {
                alphabet_num[i] = c - 65;
                cout << " " << display_text[i];
            }
        }
        cout << "\n";
    }

    void Utils::displayText(char* display_text, int alphabet_num[50], int str_length)
    {
        int i;
        str_length = strlen(display_text);

        cout << endl;
        for (i = 0; i < str_length; i++)
        {
            if (97 <= display_text[i] && display_text[i] <= 122)
            {
                alphabet_num[i] = display_text[i] - 97;
                cout << " " << (char)toupper(display_text[i]);
            }

            else if (65 <= display_text[i] && display_text[i] <= 90)
            {
                alphabet_num[i] = display_text[i] - 65;
                cout << " " << display_text[i];
            }
        } cout << endl;
    }

    void Utils::displayNumber(int num_array[50], int str_length)
    {
        int i;
        cout << endl;
        for (i = 0; i < str_length; i++)
            cout << " " << num_array[i];
        cout << endl;
    }