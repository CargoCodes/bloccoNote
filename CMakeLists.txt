cmake_minimum_required(VERSION 3.20)
project(bloccoNote)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt@5/5.15.3/lib/cmake/")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_FILES LsmL.cpp LsmL.h)

add_subdirectory(test)

find_package(Qt5Widgets REQUIRED)

add_executable(bloccoNote main.cpp Note.cpp Note.h LsmL.cpp LsmL.h GUI.cpp GUI.h NoteFolder.cpp NoteFolder.h FolderManager.cpp FolderManager.h NotesManager.cpp NotesManager.h)

add_library(core ${SOURCE_FILES})

target_link_libraries(bloccoNote Qt5::Widgets)

target_link_libraries(bloccoNote core)