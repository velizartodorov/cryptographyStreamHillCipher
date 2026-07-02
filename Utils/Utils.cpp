#include "Utils.h"
#include <cstdlib>
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

    // Prompts until a non-empty, lowercase-only string is entered.
    string readLowercaseText(const string& prompt) {
        string text;
        bool valid;
        do {
            cout << endl << prompt;
            cin >> text;
            if (cin.fail()) {
                recoverOrThrow();
            }
            valid = Utils::isLowercaseOnly(text);
            if (!valid) {
                Utils::clearScreen();
                cout << endl << " Enter text: (a-z)!" << endl;
            }
        } while (!valid);
        return text;
    }

    // Prompts until an integer within [minValue, maxValue] is entered.
    int readBoundedInt(const string& prompt, int minValue, int maxValue, const string& errorMessage) {
        int value;
        do {
            cout << endl << prompt;
            cin >> value;
            if (cin.fail()) {
                recoverOrThrow();
                value = minValue - 1;
            }
            if (value < minValue || value > maxValue) {
                cout << endl << errorMessage << endl;
            }
        } while (value < minValue || value > maxValue);
        return value;
    }

    // Prompts for every cell of an n x n Hill cipher key matrix.
    Matrix readMatrixValues(int n) {
        Matrix matrixKey(n, n);
        cout << endl << " Enter Hill key (matrix [" << n << " x " << n << "]):" << endl;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                string prompt = " Value [" + to_string(i + 1) + "," + to_string(j + 1) + "] (0-25): ";
                matrixKey[i][j] = readBoundedInt(prompt, 0, 25, " Value must be between 0 and 25!");
            }
        }
        return matrixKey;
    }
}

    void Utils::validateInput(string& charKey, string& plainText, Matrix& matrixKey) {
        setConsoleColors();

        cout << endl << " --- Stream and Hill ciphers --- " << endl;

        plainText = readLowercaseText(" Enter plain text: ");
        charKey = readLowercaseText(" Enter stream key: ");

        int n = readBoundedInt(" Enter Hill cipher matrix size (N for an N x N key matrix): ",
            1, numeric_limits<int>::max(), " Matrix size must be a positive whole number!");

        matrixKey = readMatrixValues(n);
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
        int wrapped = value % 26;
        if (wrapped < 0)
        {
            wrapped += 26;
        }
        return static_cast<char>(wrapped + 'A');
    }

    void Utils::setConsoleColors()
    {
#ifdef _WIN32
        system("color F0");
#endif
        // No portable equivalent for non-Windows terminals; left as a no-op
        // there so output stays plain rather than relying on ANSI support.
    }

    void Utils::clearScreen()
    {
#ifdef _WIN32
        system("cls");
#else
        // Raw ANSI escape sequence instead of shelling out to `clear`, which
        // prints "TERM environment variable not set" when TERM is unset
        // (e.g. in a Docker container without -e TERM=...).
        cout << "\033[2J\033[H";
#endif
    }

    void Utils::pauseConsole()
    {
#ifdef _WIN32
        system("pause");
#else
        cout << "Press Enter to continue . . . ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
#endif
    }
