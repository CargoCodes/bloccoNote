cmake_minimum_required(VERSION 3.20)
project(bloccoNote)

set(CMAKE_CXX_STANDARD 14)

add_executable(bloccoNote main.cpp Note.cpp Note.h NotesMemory.cpp NotesMemory.h utils.cpp utils.h LsmL.cpp LsmL.h)
