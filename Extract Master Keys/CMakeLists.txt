cmake_minimum_required(VERSION 3.10)
project(extractMasterKeys)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
	src/BrowserKeyExtract.cpp
    src/base64.cpp
    src/utility.cpp
)

# Header files
set(HEADERS
    include/BrowserKeyExtract.h
    include/base64.h
    include/utility.h
)

# Group source files
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files" FILES ${SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Header Files" FILES ${HEADERS})

# Enable Unicode
add_definitions(-D_UNICODE -DUNICODE)

# Executable
add_executable(extractMasterKeys ${SOURCES} ${HEADERS})

# Link with crypt32.lib
target_link_libraries(extractMasterKeys crypt32)

# Handle 32-bit and 64-bit builds
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Configuring for 64-bit build")
else()
    message(STATUS "Configuring for 32-bit build")
endif()