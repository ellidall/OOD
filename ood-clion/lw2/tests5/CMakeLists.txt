file(GLOB_RECURSE TEST_SRC "*.h" "*.cpp")
add_executable(tests5 ${TEST_SRC})

target_link_libraries(tests5
        PRIVATE
        gtest
        gtest_main
        gmock
        gmock_main
)

include(GoogleTest)
gtest_discover_tests(tests5)