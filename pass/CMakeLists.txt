cmake_minimum_required(VERSION 3.13)
project(Skel)

set(PassName "Skel")

# Find LLVM 14
find_package(LLVM 14 REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

file(GLOB PassSrc
    "*.cpp")

# Add LLVM
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(HandleLLVMOptions)
include(AddLLVM)

# LLVM headers
include_directories(${LLVM_INCLUDE_DIRS})

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add LLVM pass library
add_llvm_library(${PassName} MODULE ${PassSrc})