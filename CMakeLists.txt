cmake_minimum_required(VERSION 3.15)
project(datastructure)

set(CMAKE_CXX_STANDARD 11)
include(PrecompiledHeader.cmake)

add_executable(datastructure pch.cpp main.cpp vector/vector.h list/doublyLinkedList.h list/doublyLinkedListTest.cpp test.h)

add_precompiled_header(datastructure pch.h FORCEINCLUDE)
target_link_libraries(datastructure PUBLIC -pthread)
target_link_libraries(datastructure PUBLIC gtest)