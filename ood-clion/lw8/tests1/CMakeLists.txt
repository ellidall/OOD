file(GLOB_RECURSE TEST_SRC "*.h" "*.cpp")
add_executable(tests1 ${TEST_SRC})

target_link_libraries(tests1
        PRIVATE
        gtest
        gtest_main
        gmock
        gmock_main
)

include(GoogleTest)
gtest_discover_tests(tests1)