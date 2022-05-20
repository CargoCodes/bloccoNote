cmake_minimum_required(VERSION 3.20)
project(bloccoNote)

set(CMAKE_CXX_STANDARD 14)



set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt@5/5.15.3/lib/cmake/")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)

add_executable(bloccoNote main.cpp Note.cpp Note.h NotesMemory.cpp NotesMemory.h utils.cpp utils.h LsmL.cpp LsmL.h GUInterface.cpp GUInterface.h IdPushButton.cpp IdPushButton.h)

target_link_libraries(bloccoNote Qt5::Widgets)