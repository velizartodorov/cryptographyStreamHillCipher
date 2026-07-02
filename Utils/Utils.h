#pragma once
#include <csetjmp>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

class Utils {
public:

    static void validateInput(string& char_key, string& plain_text, vector<vector<int>>& matrix_key);
    static void inputCheck(const string& text);
    static void displayMatrix(const vector<vector<int>>& matrix);
    static void displayText(const string& display_text, vector<int>& alphabet_num);
    static void displayNumber(const vector<int>& num_array);

private:
    static jmp_buf resume_here;
};
