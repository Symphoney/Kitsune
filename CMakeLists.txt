cmake_minimum_required(VERSION 3.16)
project(Kitsune VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add executable from sources
add_executable(kitsune_linkedlist src/main.cpp
        src/main.cpp
        include/linked_list.h
        include/Queue.h
        include/Stack.h
        include/Tree.h)

target_include_directories(kitsune_linkedlist PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Uncomment to add tests
# enable_testing()
# add_subdirectory(tests)