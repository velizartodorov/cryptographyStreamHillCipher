#include "Utils.h"
#include <limits>
#include <stdexcept>

namespace {
    // Recovers from a failed extraction by discarding the bad token so the
    // next read can try again. Throws instead when the stream is genuinely
    // exhausted (EOF) — retrying forever cannot produce more input.
    void recoverOrThrow() {
        if (cin.eof()) {
            throw runtime_error("No more input available on stdin");
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

    void Utils::validateInput(string& charKey, string& plainText, Matrix& matrixKey) {
        system("color F0");

        cout << endl << " --- Stream and Hill ciphers --- " << endl;

        bool valid;
        do {
            cout << endl << " Enter plain text: ";
            cin >> plainText;
            if (cin.fail()) {
                recoverOrThrow();
            }
            valid = isLowercaseOnly(plainText);
            if (!valid) {
                system("CLS");
                cout << endl << " Enter text: (a-z)!" << endl;
            }
        } while (!valid);

        do {
            cout << endl << " Enter stream key: ";
            cin >> charKey;
            if (cin.fail()) {
                recoverOrThrow();
            }
            valid = isLowercaseOnly(charKey);
            if (!valid) {
                system("CLS");
                cout << endl << " Enter text: (a-z)!" << endl;
            }
        } while (!valid);

        int n;
        do {
            cout << endl << " Enter Hill cipher matrix size (N for an N x N key matrix): ";
            cin >> n;
            if (cin.fail()) {
                recoverOrThrow();
                n = 0;
            }
            if (n <= 0) {
                cout << endl << " Matrix size must be a positive whole number!" << endl;
            }
        } while (n <= 0);

        matrixKey = Matrix(n, n);
        cout << endl << " Enter Hill key (matrix [" << n << " x " << n << "]):" << endl;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int value;
                do {
                    cout << endl << " Value [" << i + 1 << "," << j + 1 << "] (0-25): ";
                    cin >> value;
                    if (cin.fail()) {
                        recoverOrThrow();
                        value = -1;
                    }
                    if (value < 0 || value > 25) {
                        cout << " Value must be between 0 and 25!" << endl;
                    }
                } while (value < 0 || value > 25);
                matrixKey[i][j] = value;
            }
        }
    }

    bool Utils::isLowercaseOnly(const string& text)
    {
        if (text.empty()) {
            return false;
        }
        for (char c : text)
        {
            if (!islower(static_cast<unsigned char>(c)))
            {
                return false;
            }
        }
        return true;
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
            if (islower(c)) {
                alphabetNum[i] = c - 'a';
                cout << " " << static_cast<char>(toupper(c));
            }
            else if (isupper(c)) {
                alphabetNum[i] = c - 'A';
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

    char Utils::numberToLetter(int value)
    {
        return static_cast<char>((value % 26) + 'A');
    }
