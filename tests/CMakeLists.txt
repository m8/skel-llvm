cmake_minimum_required(VERSION 3.13)
project(Tests)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -flegacy-pass-manager -Xclang -load -Xclang ${CMAKE_BINARY_DIR}/pass/Skel.so")

add_executable(function_test function.c runtime.c)
add_executable(syscall_test syscall.c runtime.c)