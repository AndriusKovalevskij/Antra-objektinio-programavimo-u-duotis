cmake_minimum_required(VERSION 3.10)

# Project name
project(v2.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files for the main executable
set(SOURCES
    main.cpp
    student.cpp
    zmogus.cpp
    operations.cpp
    file_operations.cpp
)

# Header files (for IDE organization)
set(HEADERS
    student.h
    zmogus.h
    operations.h
    file_operations.h
)

# Main executable
add_executable(v2.0 ${SOURCES} ${HEADERS})

# Build unit tests
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    # Unit test executable
    add_executable(unit_tests
        unit_tests.cpp
        student.cpp
        zmogus.cpp
        operations.cpp
        file_operations.cpp
	catch_amalgamated.cpp
	catch_amalgamated.hpp
    )
        
    enable_testing()
    add_test(NAME unit_tests COMMAND unit_tests)
endif()

