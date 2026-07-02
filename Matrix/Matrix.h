#pragma once
#include <vector>
#include <initializer_list>

using namespace std;

class Matrix {
public:
    Matrix() = default;
    Matrix(int rows, int cols); // throws invalid_argument if rows or cols is negative
    Matrix(initializer_list<initializer_list<int>> init); // throws invalid_argument if rows differ in length

    vector<int>& operator[](size_t row);
    const vector<int>& operator[](size_t row) const;

    size_t size() const; // row count

    vector<vector<int>>::iterator begin();
    vector<vector<int>>::iterator end();
    vector<vector<int>>::const_iterator begin() const;
    vector<vector<int>>::const_iterator end() const;

private:
    vector<vector<int>> data;
};
