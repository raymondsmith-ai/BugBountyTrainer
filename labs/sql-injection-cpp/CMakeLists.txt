cmake_minimum_required(VERSION 3.16)

project(BugBountyTrainerSQLLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Locate SQLite3.
find_package(SQLite3 REQUIRED)

# Build the C++ training server.
add_executable(
    bbt_sql_lab
    main.cpp
    Database.cpp
    LessonManager.cpp
)

# Link SQLite3 to the application.
target_link_libraries(
    bbt_sql_lab
    PRIVATE
    SQLite::SQLite3
)

target_compile_options(
    bbt_sql_lab
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)