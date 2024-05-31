cmake_minimum_required(VERSION 3.15)
project(testBinaryTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
        Test.cpp binaryTree.h binaryTreeNode.h linkedBinaryTree.h)

#add_precompiled_header(datastructure pch.h FORCEINCLUDE)
target_link_libraries(${PROJECT_NAME} PUBLIC -pthread)

#set(CMAKE_CXX_FLAGS "-Wreturn-type")
