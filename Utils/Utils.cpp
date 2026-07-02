#include "Utils.h"

jmp_buf Utils::resume_here;

    void Utils::validateInput(string& char_key, string& plain_text, vector<vector<int>>& matrix_key) {
        system("color F0");

        if (setjmp(resume_here) != 0)
        {
            cout << "";
        }
        cout << endl << " --- Stream and Hill ciphers --- " << endl;

        cout << endl << " Enter plain text: ";
        cin >> plain_text;

        inputCheck(plain_text);

        if (setjmp(resume_here) != 0)
        {
            cout << "";
        }

        cout << endl << " Enter stream key: ";
        cin >> char_key;

       inputCheck(char_key);

       int n;
       cout << endl << " Enter Hill cipher matrix size (N for an N x N key matrix): ";
       cin >> n;

       matrix_key.assign(n, vector<int>(n));
       cout << endl << " Enter Hill key (matrix [" << n << " x " << n << "]):" << endl;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << endl << " Value [" << i + 1 << "," << j + 1 << "]: ";
                cin >> matrix_key[i][j];
            }
        }
    }

    void Utils::inputCheck(const string& text)
    {
        int str_length = static_cast<int>(text.length());

        for (int i = 0; i < str_length; i++)
        {
            if (!(97 <= text[i] && text[i] <= 122))
            {
                system("CLS");
                cout << endl << " Enter text: (a-z)!" << endl;
                longjmp(resume_here, 1);
            }
        }
    }

    void Utils::displayMatrix(const vector<vector<int>>& matrix) {
        cout << "\n";
        for (const auto& row : matrix) {
            cout << "\n";
            for (int value : row) cout << "  " << value;
            cout << "\n";
        }
    }

    void Utils::displayText(const string& display_text, vector<int>& alphabet_num) {
        int n = static_cast<int>(display_text.length());
        alphabet_num.assign(n, 0);
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

    void Utils::displayNumber(const vector<int>& num_array)
    {
        cout << endl;
        for (int value : num_array)
            cout << " " << value;
        cout << endl;
    }
