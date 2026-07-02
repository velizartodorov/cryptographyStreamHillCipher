cmake_minimum_required(VERSION 3.10)
project(StreamHillCipherEncoding CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_library(cipher_core
    HillCipher/HillCipher.cpp
    StreamCipher/StreamCipher.cpp
    Utils/Utils.cpp
    Matrix/Matrix.cpp
)
target_include_directories(cipher_core PUBLIC
    HillCipher
    StreamCipher
    Utils
    Matrix
)

add_executable(StreamHillCipherEncoding StreamHillCipherEncoding.cpp)
target_link_libraries(StreamHillCipherEncoding PRIVATE cipher_core)

add_executable(TestProject
    tests/TestRunner.cpp
    tests/HillCipherTest.cpp
    tests/StreamCipherTest.cpp
    tests/UtilsTest.cpp
    tests/IntegrationTest.cpp
    tests/MatrixTest.cpp
)
target_include_directories(TestProject PRIVATE tests)
target_link_libraries(TestProject PRIVATE cipher_core)

enable_testing()
add_test(NAME AllTests COMMAND TestProject)
