cmake_minimum_required(VERSION 3.14)
project(Project LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(googletest-main)

add_executable(run_tests
    my_tests.cpp
    main.h
)

target_include_directories(run_tests PRIVATE googletest-main/googletest/include)
target_link_libraries(run_tests PRIVATE gtest_main)