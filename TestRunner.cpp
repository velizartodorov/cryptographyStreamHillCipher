#include "TestFramework.h"
#include <iostream>

// Include all test files
// Note: The actual test functions are registered automatically via the TEST macro

int main() {
    cout << "StreamHillCipherEncoding Test Suite\n";
    cout << "===================================\n\n";
    
    // Run all registered tests
    TestFramework::getInstance().runAllTests();
    
    cout << "\nPress any key to exit...";
    cin.get();
    
    return 0;
}
