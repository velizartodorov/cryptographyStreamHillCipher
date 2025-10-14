#pragma once
#include <csetjmp>
#include <cstring>
#include <iostream>
#include <conio.h>

using namespace std;

class Utils {
public:
    
    static void validateInput(char char_key[50], char plain_text[50], char cipher_text[50], int matrix_key[25][25]);
    static void inputCheck(char* text, int str_length);
    static void displayMatrix(int row, int column, int matrix[25][25]);
    static void displayText(char* display_text, int alphabet_num[50]);
    static void displayText(char* display_text, int alphabet_num[50], int str_length);
    static void displayNumber(int num_array[50], int str_length);

private:
    static jmp_buf resume_here;
};