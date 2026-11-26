cmake_minimum_required(VERSION 4.3.0)
project(my-snake-game C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(snakegame src/snake_game.c
    include/snake_game.h)
target_include_directories(snakegame PRIVATE include)
target_compile_options(snakegame PRIVATE -Wall -Wextra)