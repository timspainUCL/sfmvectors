cmake_minimum_required(VERSION 3.0)

project(sfm)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(test_pbc test/pbc.cpp
	src/pos2d.cpp
	)
add_test(test_pbc_test test_pbc)