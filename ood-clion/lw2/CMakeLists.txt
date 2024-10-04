cmake_minimum_required(VERSION 3.22.1)
project(lw2)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(task1)
add_subdirectory(task2)
add_subdirectory(task3)
add_subdirectory(task4)
add_subdirectory(task5)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(tests2)
add_subdirectory(tests3)
add_subdirectory(tests4)
add_subdirectory(tests5)