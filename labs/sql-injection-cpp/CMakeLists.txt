cmake_minimum_required(VERSION 3.16)

project(BugBountyTrainerSQLLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(bbt_sql_lab main.cpp)

target_compile_options(
    bbt_sql_lab
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)