#include "TestFramework.h"
#include "Matrix.h"

// Test that the (rows, cols) constructor builds a zero-filled matrix of the
// requested shape.
TEST(Matrix_SizedConstructor) {
    Matrix m(2, 3);
    ASSERT_EQUAL(2, static_cast<int>(m.size()));
    for (const auto& row : m) {
        ASSERT_EQUAL(3, static_cast<int>(row.size()));
        for (int value : row) {
            ASSERT_EQUAL(0, value);
        }
    }
}

// Test that a well-formed initializer-list literal builds correctly.
TEST(Matrix_LiteralConstructor) {
    Matrix m = {{1, 2}, {3, 4}};
    ASSERT_EQUAL(2, static_cast<int>(m.size()));
    ASSERT_EQUAL(1, m[0][0]);
    ASSERT_EQUAL(4, m[1][1]);
}

// Test that negative dimensions are rejected rather than silently converted
// to a huge size_t and crashing with bad_alloc/length_error.
TEST(Matrix_NegativeDimensions_Throws) {
    bool threw = false;
    try {
        Matrix m(-1, -1);
    } catch (const invalid_argument&) {
        threw = true;
    }
    ASSERT_TRUE(threw);
}

// Test that a jagged (unequal row length) literal is rejected rather than
// silently building a matrix that overflows when indexed as rectangular.
TEST(Matrix_JaggedLiteral_Throws) {
    bool threw = false;
    try {
        Matrix m = {{1, 2, 3}, {4, 5}};
    } catch (const invalid_argument&) {
        threw = true;
    }
    ASSERT_TRUE(threw);
}
