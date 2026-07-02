#pragma once
#include <csetjmp>
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
    static void inputCheck(const string& text);
    static void displayMatrix(const Matrix& matrix);
    static void displayText(const string& text, vector<int>& alphabetNum);
    static void displayNumber(const vector<int>& numArray);

private:
    static jmp_buf resumeHere;
};
