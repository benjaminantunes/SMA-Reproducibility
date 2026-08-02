cmake_minimum_required(VERSION 3.20)
project(TP1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_compile_options("-Ofast")            # hard optimize
add_compile_options("-fno-fast-math")    # unbreak math
add_compile_options("-flto")             # link optimize
add_compile_options("-march=native")     # cpu optimize

add_compile_options("-Wall")
add_compile_options("-Wextra")
add_compile_options("-pedantic")

add_executable(TP1 main.cpp
        src/Random.cpp
        src/Human.cpp
        src/Simulation.cpp)

include_directories("include")
