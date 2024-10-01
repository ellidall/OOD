file(GLOB_RECURSE TEST_SRC "*.h" "*.cpp")
add_executable(tests2 ${TEST_SRC})

target_link_libraries(tests2
        PRIVATE
        gtest
        gtest_main
        gmock
        gmock_main
)

include(GoogleTest)
gtest_discover_tests(tests2)