cmake_minimum_required(VERSION 3.15)
project(testRedBlackTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
        rbTreeNode.h rbTree.h
        Test.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC .
        ../binaryTree
        ../dictionary)

#add_precompiled_header(datastructure pch.h FORCEINCLUDE)
target_link_libraries(${PROJECT_NAME} PUBLIC -pthread)

#set(CMAKE_CXX_FLAGS "-Wreturn-type")
