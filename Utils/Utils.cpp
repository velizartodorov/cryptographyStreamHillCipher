#include "Utils.h"

jmp_buf Utils::resumeHere;

    void Utils::validateInput(string& charKey, string& plainText, Matrix& matrixKey) {
        system("color F0");

        if (setjmp(resumeHere) != 0)
        {
            cout << "";
        }
        cout << endl << " --- Stream and Hill ciphers --- " << endl;

        cout << endl << " Enter plain text: ";
        cin >> plainText;

        inputCheck(plainText);

        if (setjmp(resumeHere) != 0)
        {
            cout << "";
        }

        cout << endl << " Enter stream key: ";
        cin >> charKey;

       inputCheck(charKey);

       int n;
       cout << endl << " Enter Hill cipher matrix size (N for an N x N key matrix): ";
       cin >> n;

       matrixKey = Matrix(n, n);
       cout << endl << " Enter Hill key (matrix [" << n << " x " << n << "]):" << endl;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << endl << " Value [" << i + 1 << "," << j + 1 << "]: ";
                cin >> matrixKey[i][j];
            }
        }
    }

    void Utils::inputCheck(const string& text)
    {
        int strLength = static_cast<int>(text.length());

        for (int i = 0; i < strLength; i++)
        {
            if (!(97 <= text[i] && text[i] <= 122))
            {
                system("CLS");
                cout << endl << " Enter text: (a-z)!" << endl;
                longjmp(resumeHere, 1);
            }
        }
    }

    void Utils::displayMatrix(const Matrix& matrix) {
        cout << "\n";
        for (const auto& row : matrix) {
            cout << "\n";
            for (int value : row) cout << "  " << value;
            cout << "\n";
        }
    }

    void Utils::displayText(const string& text, vector<int>& alphabetNum) {
        int n = static_cast<int>(text.length());
        alphabetNum.assign(n, 0);
        cout << "\n";
        for (int i = 0; i < n; ++i) {
            unsigned char c = static_cast<unsigned char>(text[i]);
            if (97 <= c && c <= 122) {
                alphabetNum[i] = c - 97;
                cout << " " << static_cast<char>(toupper(c));
            }
            else if (65 <= c && c <= 90) {
                alphabetNum[i] = c - 65;
                cout << " " << text[i];
            }
        }
        cout << "\n";
    }

    void Utils::displayNumber(const vector<int>& numArray)
    {
        cout << endl;
        for (int value : numArray)
            cout << " " << value;
        cout << endl;
    }
