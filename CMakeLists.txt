cmake_minimum_required(VERSION 3.16)
project(Kitsune VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add executable from sources
add_executable(kitsune_linkedlist src/main.cpp
        src/main.cpp
        "include/Basic Data Structures/LinkedList.h"
        "include/Basic Data Structures/Queue.h"
        "include/Basic Data Structures/Stack.h"
        "include/Basic Data Structures/Tree.h"
        include/Linux/console_output.h
        include/Design/Adapter/vector_raster.h
        include/mouse_track.h)

target_include_directories(kitsune_linkedlist PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Uncomment to add tests
# enable_testing()
# add_subdirectory(tests)