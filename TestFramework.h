#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <cassert>
#include <exception>
#include <stdexcept>

using namespace std;

class TestFramework {
public:
    struct TestCase {
        string name;
        function<void()> testFunction;
        bool passed;
        string errorMessage;
    };

    static TestFramework& getInstance() {
        static TestFramework instance;
        return instance;
    }

    void addTest(const string& name, function<void()> testFunction) {
        testCases.push_back({name, testFunction, false, ""});
    }

    void runAllTests() {
        cout << "Running " << testCases.size() << " tests...\n\n";
        
        int passed = 0;
        int failed = 0;

        for (auto& testCase : testCases) {
            try {
                testCase.testFunction();
                testCase.passed = true;
                passed++;
                cout << "✓ " << testCase.name << " - PASSED\n";
            } catch (const exception& e) {
                testCase.passed = false;
                testCase.errorMessage = e.what();
                failed++;
                cout << "✗ " << testCase.name << " - FAILED: " << e.what() << "\n";
            } catch (...) {
                testCase.passed = false;
                testCase.errorMessage = "Unknown error";
                failed++;
                cout << "✗ " << testCase.name << " - FAILED: Unknown error\n";
            }
        }

        cout << "\n" << string(50, '=') << "\n";
        cout << "Test Results: " << passed << " passed, " << failed << " failed\n";
        cout << string(50, '=') << "\n";

        if (failed > 0) {
            cout << "\nFailed Tests:\n";
            for (const auto& testCase : testCases) {
                if (!testCase.passed) {
                    cout << "- " << testCase.name << ": " << testCase.errorMessage << "\n";
                }
            }
        }
    }

private:
    vector<TestCase> testCases;
};

// Assertion macros
#define ASSERT_TRUE(condition) \
    if (!(condition)) { \
        throw runtime_error("Assertion failed: " #condition " is not true"); \
    }

#define ASSERT_FALSE(condition) \
    if (condition) { \
        throw runtime_error("Assertion failed: " #condition " is not false"); \
    }

#define ASSERT_EQUAL(expected, actual) \
    if ((expected) != (actual)) { \
        throw runtime_error("Assertion failed: Expected " + to_string(expected) + ", got " + to_string(actual)); \
    }

#define ASSERT_STRING_EQUAL(expected, actual) \
    if (string(expected) != string(actual)) { \
        throw runtime_error("Assertion failed: Expected '" + string(expected) + "', got '" + string(actual) + "'"); \
    }

#define ASSERT_NOT_NULL(ptr) \
    if (ptr == nullptr) { \
        throw runtime_error("Assertion failed: Pointer is null"); \
    }

#define ASSERT_NULL(ptr) \
    if (ptr != nullptr) { \
        throw runtime_error("Assertion failed: Pointer is not null"); \
    }

// Test registration macro
#define TEST(name) \
    void test_##name(); \
    struct TestRegistrar_##name { \
        TestRegistrar_##name() { \
            TestFramework::getInstance().addTest(#name, test_##name); \
        } \
    }; \
    static TestRegistrar_##name testRegistrar_##name; \
    void test_##name()
