# StreamHillCipherEncoding Test Suite

[![CI Tests](https://github.com/yourusername/StreamHillCipherEncoding/workflows/CI%20Tests/badge.svg)](https://github.com/yourusername/StreamHillCipherEncoding/actions/workflows/ci.yml)
[![Build and Test](https://github.com/yourusername/StreamHillCipherEncoding/workflows/Build%20and%20Test/badge.svg)](https://github.com/yourusername/StreamHillCipherEncoding/actions/workflows/build-and-test.yml)
[![Code Quality](https://github.com/yourusername/StreamHillCipherEncoding/workflows/Code%20Quality/badge.svg)](https://github.com/yourusername/StreamHillCipherEncoding/actions/workflows/code-quality.yml)
[![Security Scan](https://github.com/yourusername/StreamHillCipherEncoding/workflows/Security%20Scan/badge.svg)](https://github.com/yourusername/StreamHillCipherEncoding/actions/workflows/security.yml)

This document describes the comprehensive test suite for the StreamHillCipherEncoding project.

## Overview

The test suite includes:
- **Unit Tests** for individual components (StreamCipher, HillCipher, Utils)
- **Integration Tests** for the complete encryption pipeline
- **Custom Test Framework** with assertion macros and test runner

## Test Structure

### Test Framework (`TestFramework.h`)
- Custom lightweight testing framework
- Assertion macros: `ASSERT_TRUE`, `ASSERT_FALSE`, `ASSERT_EQUAL`, `ASSERT_STRING_EQUAL`, etc.
- Automatic test registration via `TEST` macro
- Detailed test results reporting

### Unit Tests

#### StreamCipher Tests (`StreamCipherTest.cpp`)
- `StreamCipher_BasicEncoding`: Tests basic stream cipher functionality
- `StreamCipher_DifferentKeyLengths`: Tests with various key lengths
- `StreamCipher_EmptyInput`: Tests edge case with empty input
- `StreamCipher_KeyCycling`: Tests key cycling behavior for long texts
- `StreamCipher_SpecialCharacters`: Tests handling of invalid characters

#### HillCipher Tests (`HillCipherTest.cpp`)
- `HillCipher_BasicEncoding`: Tests basic Hill cipher functionality
- `HillCipher_EvenLengthText`: Tests with even-length plaintext
- `HillCipher_OddLengthText`: Tests with odd-length plaintext (padding)
- `HillCipher_SingleCharacter`: Tests with single character input
- `HillCipher_IdentityMatrix`: Tests with identity matrix key
- `HillCipher_DifferentMatrixValues`: Tests with various matrix configurations
- `HillCipher_UppercaseText`: Tests with uppercase input
- `HillCipher_MixedCaseText`: Tests with mixed case input
- `HillCipher_LongText`: Tests with long text input

#### Utils Tests (`UtilsTest.cpp`)
- `Utils_DisplayTextLowercase`: Tests text display with lowercase input
- `Utils_DisplayTextUppercase`: Tests text display with uppercase input
- `Utils_DisplayTextMixedCase`: Tests text display with mixed case input
- `Utils_DisplayTextWithLength`: Tests text display with specified length
- `Utils_DisplayNumber`: Tests number array display
- `Utils_DisplayMatrix`: Tests matrix display
- `Utils_InputCheckValidLowercase`: Tests input validation with valid lowercase
- `Utils_InputCheckInvalidNumbers`: Tests input validation with numbers
- `Utils_InputCheckUppercase`: Tests input validation with uppercase
- `Utils_InputCheckSpecialCharacters`: Tests input validation with special characters
- `Utils_InputCheckEmptyString`: Tests input validation with empty string

### Integration Tests (`IntegrationTest.cpp`)
- `Integration_StreamThenHillCipher`: Tests complete encryption pipeline
- `Integration_DifferentTextLengths`: Tests with various text lengths
- `Integration_DifferentKeys`: Tests with different stream cipher keys
- `Integration_DifferentMatrixKeys`: Tests with different Hill cipher matrices
- `Integration_EncryptionConsistency`: Tests encryption consistency
- `Integration_EdgeCases`: Tests edge cases (single char, two chars, etc.)
- `Integration_AlphabetBoundaryCases`: Tests boundary cases (a, z, full alphabet)

## Building and Running Tests

### Option 1: Using the Main Project
1. Build the main project (`StreamHillCipherEncoding.vcxproj`)
2. The test files are included in the main project
3. Run the executable to see both the main program and tests

### Option 2: Using the Test Project (Recommended)
1. Open `TestProject.vcxproj` in Visual Studio
2. Build the project (Debug or Release configuration)
3. Run the generated executable to execute all tests

### Option 3: Command Line
```bash
# Build the test project
msbuild TestProject.vcxproj /p:Configuration=Debug /p:Platform=x64

# Run the tests
./x64/Debug/TestProject.exe
```

## Test Output

The test runner provides detailed output including:
- Test execution progress
- Pass/fail status for each test
- Error messages for failed tests
- Summary statistics
- List of failed tests with error details

Example output:
```
StreamHillCipherEncoding Test Suite
===================================

Running 25 tests...

✓ StreamCipher_BasicEncoding - PASSED
✓ HillCipher_BasicEncoding - PASSED
✓ Utils_DisplayTextLowercase - PASSED
✗ Utils_InputCheckUppercase - FAILED: Assertion failed: condition is not false

==================================================
Test Results: 24 passed, 1 failed
==================================================

Failed Tests:
- Utils_InputCheckUppercase: Assertion failed: condition is not false
```

## Test Limitations

Due to the interactive nature of the original code (using `_getche()` for user input), some tests focus on:
- Verifying functions complete without crashing
- Testing input validation logic
- Ensuring proper data transformation
- Validating mathematical operations

The tests are designed to be non-interactive and can run automatically in CI/CD pipelines.

## Adding New Tests

To add new tests:

1. Create a new test function using the `TEST` macro:
```cpp
TEST(MyNewTest) {
    // Test code here
    ASSERT_TRUE(condition);
}
```

2. The test will be automatically registered and run with all other tests.

## Test Coverage

The test suite covers:
- ✅ Basic functionality of all classes
- ✅ Edge cases and boundary conditions
- ✅ Input validation
- ✅ Error handling
- ✅ Integration between components
- ✅ Various input scenarios (different lengths, cases, keys)

## Continuous Integration (CI/CD)

### GitHub Actions Workflows

The project includes comprehensive GitHub Actions workflows for automated testing and quality assurance:

#### 🔄 **CI Tests** (`.github/workflows/ci.yml`)
- **Triggers**: Push to main/master/develop, Pull Requests
- **Purpose**: Quick validation of test suite
- **Runs**: Windows latest with MSBuild
- **Actions**: Build test project, run tests, build main project

#### 🏗️ **Build and Test** (`.github/workflows/build-and-test.yml`)
- **Triggers**: Push to main/master/develop, Pull Requests, Manual dispatch
- **Purpose**: Comprehensive build matrix testing
- **Matrix**: Debug/Release configurations, x64 platform
- **Actions**: Clean build, verify executables, run tests, archive artifacts

#### 🔍 **Code Quality** (`.github/workflows/code-quality.yml`)
- **Triggers**: Push to main/master/develop, Pull Requests
- **Purpose**: Code quality and best practices validation
- **Checks**: Warnings as errors, TODO detection, debug code, hardcoded paths
- **Actions**: Build with strict warnings, validate project structure

#### 🔒 **Security Scan** (`.github/workflows/security.yml`)
- **Triggers**: Push to main/master/develop, Pull Requests, Weekly schedule
- **Purpose**: Security vulnerability detection
- **Tools**: CodeQL analysis, security anti-pattern detection
- **Checks**: Unsafe functions, buffer overflows, memory management, secrets

#### 🚀 **Release Build** (`.github/workflows/release.yml`)
- **Triggers**: Tag pushes (v*), Manual dispatch
- **Purpose**: Automated release packaging
- **Actions**: Release build, test validation, ZIP packaging, GitHub release

### Workflow Features

- **Multi-configuration testing**: Debug and Release builds
- **Artifact archiving**: Build outputs and test results preserved
- **Security scanning**: Automated vulnerability detection
- **Code quality checks**: Best practices enforcement
- **Release automation**: Tag-based release builds
- **Status badges**: Real-time workflow status display

### Local CI Simulation

To simulate CI locally, use the provided batch file:
```bash
run_tests.bat
```

Or manually:
```bash
# Build and test
msbuild TestProject.vcxproj /p:Configuration=Debug /p:Platform=x64
x64\Debug\TestProject.exe

# Build with warnings as errors (CI simulation)
msbuild TestProject.vcxproj /p:Configuration=Debug /p:Platform=x64 /p:TreatWarningsAsErrors=true
```

### Workflow Status

Check the [Actions tab](https://github.com/yourusername/StreamHillCipherEncoding/actions) in your GitHub repository to view:
- Real-time workflow execution
- Test results and logs
- Build artifacts
- Security scan reports
- Release builds

## Notes

- Tests are designed to be platform-independent (Windows-specific code is handled gracefully)
- The test framework is lightweight and doesn't require external dependencies
- All tests can run without user interaction
- Test results are clearly formatted for easy analysis
- **CI/CD Integration**: All workflows run automatically on every commit
- **Security**: Regular security scans and code quality checks
- **Releases**: Automated release builds with test validation
