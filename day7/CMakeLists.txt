add_library(day7_common STATIC day7.cpp)

add_executable(day7_main
        day7_main.cpp)
target_link_libraries(day7_main
                      day7_common
                      common)

add_executable(day7_test
        day7_test.cpp)
target_link_libraries(day7_test
                      day7_common
                      gtest_main
                      common)

gtest_discover_tests(day7_test)
