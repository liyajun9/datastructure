cmake_minimum_required(VERSION 3.15)
project(datastructure)

set(CMAKE_CXX_STANDARD 11)
include(PrecompiledHeader.cmake)

add_executable(datastructure
        pch.cpp
        main.cpp
        vector/vector.h
        stack/stack.h
        sort/sort.h
        sort/search.h
        queue/listQueue.h
        test.h
        list/doublyLinkedList.h list/doublyLinkedListTest.cpp
        skipList/skipList.h
        test/sortTest.cpp
        test/searchTest.cpp
        test/stackTest.cpp
        stl/binary_heap.hpp
        priority_queue/maxHeap.h
        priority_queue/maxHblt.h
        priority_queue/maxPriorityQueue.h
        priority_queue/Test.cpp winnerTree/Test.cpp winnerTree/player.h)

add_precompiled_header(datastructure pch.h FORCEINCLUDE)
target_link_libraries(datastructure PUBLIC -pthread)

#set(CMAKE_CXX_FLAGS "-Wreturn-type")