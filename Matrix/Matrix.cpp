#include "Matrix.h"
#include <stdexcept>

Matrix::Matrix(int rows, int cols) {
    if (rows < 0 || cols < 0) {
        throw invalid_argument("Matrix: rows and cols must be non-negative");
    }
    data.assign(rows, vector<int>(cols, 0));
}

Matrix::Matrix(initializer_list<initializer_list<int>> init) {
    for (const auto& row : init) {
        if (!data.empty() && row.size() != data[0].size()) {
            throw invalid_argument("Matrix: all rows must have the same length");
        }
        data.emplace_back(row);
    }
}

vector<int>& Matrix::operator[](size_t row) { return data[row]; }
const vector<int>& Matrix::operator[](size_t row) const { return data[row]; }

size_t Matrix::size() const { return data.size(); }

vector<vector<int>>::iterator Matrix::begin() { return data.begin(); }
vector<vector<int>>::iterator Matrix::end() { return data.end(); }
vector<vector<int>>::const_iterator Matrix::begin() const { return data.begin(); }
vector<vector<int>>::const_iterator Matrix::end() const { return data.end(); }
