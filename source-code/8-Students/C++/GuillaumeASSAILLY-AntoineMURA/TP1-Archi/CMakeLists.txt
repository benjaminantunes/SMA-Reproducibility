cmake_minimum_required(VERSION 3.26)
project(TP1_Archi)

set(CMAKE_CXX_STANDARD 23)

add_executable(TP1_Archi main.cpp
        objects/World.h
        objects/Subject.h
        utils/Random.cpp
        utils/Random.h
        objects/World.cpp
        utils/IMover.h
        utils/RandomMover.cpp
        utils/RandomMover.h
        objects/Subject.cpp
        utils/FileWriter.cpp
        utils/FileWriter.h
)
