cmake_minimum_required(VERSION 3.0)

project(sfm)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_executable(test_pbc test/pbc.cpp
	src/pos2d.cpp
	)
target_compile_definitions(test_pbc PRIVATE POS2D_XWRAP=5 POS2D_YWRAP=3)
add_test(test_pbc_test test_pbc)

add_executable(test_pbc8024 test/pbc8024.cpp
	src/pos2d.cpp
	)
target_compile_definitions(test_pbc8024 PRIVATE POS2D_XWRAP=80 POS2D_YWRAP=24)
add_test(test_pbc8024_test test_pbc8024)

add_executable(test_dir test/dirtest.cpp
	src/dir2d.cpp
	src/pos2d.cpp
	)
target_compile_definitions(test_dir PRIVATE POS2D_XWRAP=5 POS2D_YWRAP=3)
add_test(test_dir_test test_dir)