file(GLOB_RECURSE TEST_SRC "*.h" "*.cpp")
add_executable(Test_SimUDuck ${TEST_SRC})

target_link_libraries(Test_SimUDuck
        PRIVATE
        gtest
        gtest_main
        gmock
        gmock_main
)

include(GoogleTest)
gtest_discover_tests(Test_SimUDuck)