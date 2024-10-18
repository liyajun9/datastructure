cmake_minimum_required(VERSION 3.15)
project(TestFibonacci)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
        Test.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC -pthread)
