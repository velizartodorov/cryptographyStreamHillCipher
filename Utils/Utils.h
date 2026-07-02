#pragma once
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "Matrix.h"

using namespace std;

class Utils {
public:

    static void validateInput(string& charKey, string& plainText, Matrix& matrixKey);
    static bool isLowercaseOnly(const string& text);
    static void displayMatrix(const Matrix& matrix);
    static void displayText(const string& text, vector<int>& alphabetNum);
    static void displayNumber(const vector<int>& numArray);
    static char numberToLetter(int value); // value must be non-negative
};
