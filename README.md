# StreamHillCipherEncoding

[![CI Tests](https://github.com/velizartodorov/cryptographyStreamHillCipher/actions/workflows/ci.yml/badge.svg)](https://github.com/velizartodorov/cryptographyStreamHillCipher/actions/workflows/ci.yml)
[![Build and Test](https://github.com/velizartodorov/cryptographyStreamHillCipher/actions/workflows/build-and-test.yml/badge.svg)](https://github.com/velizartodorov/cryptographyStreamHillCipher/actions/workflows/build-and-test.yml)
[![Code Quality](https://github.com/velizartodorov/cryptographyStreamHillCipher/actions/workflows/code-quality.yml/badge.svg)](https://github.com/velizartodorov/cryptographyStreamHillCipher/actions/workflows/code-quality.yml)
[![Security Scan](https://github.com/velizartodorov/cryptographyStreamHillCipher/actions/workflows/security.yml/badge.svg)](https://github.com/velizartodorov/cryptographyStreamHillCipher/actions/workflows/security.yml)

A C++ implementation of combined Stream Cipher and Hill Cipher encryption algorithms with comprehensive testing and CI/CD integration.

## 🔐 Overview

This project implements a hybrid encryption system that combines:
- **Stream Cipher**: For initial encryption using a repeating key
- **Hill Cipher**: For secondary encryption using matrix multiplication

The combination provides enhanced security through multiple layers of encryption.

## 🏗️ Architecture

### Core Components

- **`StreamCipher`**: Implements stream cipher encryption with key cycling
- **`HillCipher`**: Implements Hill cipher encryption using 2x2 matrices
- **`Utils`**: Utility functions for input validation, display, and matrix operations
- **`TestFramework`**: Custom testing framework with comprehensive assertions

### File Structure

```
cryptographyStreamHillCipher/
├── StreamCipher/
│   ├── StreamCipher.cpp         # Stream cipher implementation
│   └── StreamCipher.h
├── HillCipher/
│   ├── HillCipher.cpp           # Hill cipher implementation
│   └── HillCipher.h
├── Utils/
│   ├── Utils.cpp                # Utility functions
│   └── Utils.h
├── tests/
│   ├── TestFramework.h          # Custom test framework
│   ├── TestRunner.cpp           # Test execution
│   └── *Test.cpp                # Unit and integration tests
├── StreamHillCipherEncoding.cpp # Main application
├── .github/workflows/           # CI/CD workflows
└── README_TESTS.md              # Detailed testing documentation
```

## 🚀 Quick Start

### Prerequisites

- **Windows 10/11** (primary platform)
- **Visual Studio 2019/2022** with C++ development tools
- **MSBuild** (included with Visual Studio)

### Building

#### Option 1: Visual Studio
1. Open `StreamHillCipherEncoding.vcxproj`
2. Select configuration (Debug/Release) and platform (x64)
3. Build → Build Solution (Ctrl+Shift+B)

#### Option 2: Command Line
```bash
# Build main project
msbuild StreamHillCipherEncoding.vcxproj /p:Configuration=Debug /p:Platform=x64

# Build test project
msbuild TestProject.vcxproj /p:Configuration=Debug /p:Platform=x64
```

### Running

#### Main Application
```bash
x64\Debug\StreamHillCipherEncoding.exe
```

#### Test Suite
```bash
# Using batch file
run_tests.bat

# Direct execution
x64\Debug\TestProject.exe
```

## 🧪 Testing

### Test Suite Overview

The project includes a comprehensive test suite with **31+ tests** covering:

- **Unit Tests**: Individual component testing
- **Integration Tests**: End-to-end encryption pipeline
- **Edge Cases**: Boundary conditions and error handling
- **Input Validation**: Various input scenarios

### Running Tests

```bash
# Quick test run
run_tests.bat

# Manual test execution
msbuild TestProject.vcxproj /p:Configuration=Debug /p:Platform=x64
x64\Debug\TestProject.exe
```

### Test Coverage

- ✅ Stream Cipher functionality
- ✅ Hill Cipher functionality  
- ✅ Utility functions
- ✅ Input validation
- ✅ Error handling
- ✅ Integration scenarios
- ✅ Edge cases and boundaries

See [README_TESTS.md](README_TESTS.md) for detailed testing documentation.

## 🔄 Continuous Integration

### GitHub Actions Workflows

- **🔄 CI Tests**: Quick validation on every commit
- **🏗️ Build and Test**: Comprehensive build matrix testing
- **🔍 Code Quality**: Best practices and warning enforcement
- **🔒 Security Scan**: Vulnerability detection and CodeQL analysis
- **🚀 Release Build**: Automated release packaging

### Workflow Triggers

- **Push** to main/master/develop branches
- **Pull Requests** to main/master/develop branches
- **Tags** (for release builds)
- **Manual dispatch** (for on-demand testing)

## 🔧 Usage

### Basic Encryption Flow

1. **Input**: Plain text and encryption keys
2. **Stream Cipher**: First layer encryption with key cycling
3. **Hill Cipher**: Second layer encryption with matrix multiplication
4. **Output**: Encrypted ciphertext

### Example

```cpp
// Initialize ciphers
StreamCipher streamCipher;
HillCipher hillCipher;

// Encryption keys
char streamKey[] = "key";
int hillMatrix[2][2] = {{3, 3}, {2, 5}};

// Encrypt
char plainText[] = "hello";
char cipherText[50];

streamCipher.encode(plainText, cipherText, streamKey);
hillCipher.encode(cipherText, hillMatrix);
```

## 📊 Performance

- **Build Time**: ~30 seconds (Debug), ~45 seconds (Release)
- **Test Execution**: ~5 seconds for full test suite
- **Memory Usage**: Minimal (stack-based implementation)
- **Platform Support**: Windows x64 (primary), x86 (compatible)

## 🔒 Security Considerations

- **Input Validation**: Strict character validation (a-z only)
- **Buffer Management**: Fixed-size buffers with bounds checking
- **Key Management**: Keys processed in memory only
- **No External Dependencies**: Self-contained implementation

## 🤝 Contributing

### Development Workflow

1. **Fork** the repository
2. **Create** a feature branch
3. **Implement** changes with tests
4. **Run** the test suite locally
5. **Submit** a pull request

### Code Standards

- **C++17** standard compliance
- **Consistent** naming conventions
- **Comprehensive** test coverage
- **Clear** documentation and comments

### Testing Requirements

- All new features must include tests
- Existing tests must continue to pass
- Code coverage should be maintained
- Integration tests for new workflows

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🐛 Issues and Support

- **Bug Reports**: Use the [bug report template](.github/ISSUE_TEMPLATE/bug_report.md)
- **Feature Requests**: Use the [feature request template](.github/ISSUE_TEMPLATE/feature_request.md)
- **Questions**: Open a discussion or issue

## 📚 Documentation

- **[Test Documentation](README_TESTS.md)**: Comprehensive testing guide
- **[API Documentation](docs/)**: Detailed API reference (coming soon)
- **[Examples](examples/)**: Usage examples and tutorials (coming soon)

## 🏆 Acknowledgments

- Cryptographic algorithm implementations
- Testing framework design
- CI/CD pipeline configuration
- Documentation and examples

---

**Built with ❤️ using C++ and modern development practices**
