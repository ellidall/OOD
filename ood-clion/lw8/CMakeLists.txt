cmake_minimum_required(VERSION 3.22.1)
project(lw8)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(task1)
add_subdirectory(task2-4)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(tests1)
add_subdirectory(tests2-4)