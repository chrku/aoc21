add_library(day10_common STATIC day10.cpp)

add_executable(day10_main
        day10_main.cpp)
target_link_libraries(day10_main
                      day10_common
                      common)

add_executable(day10_test
        day10_test.cpp)
target_link_libraries(day10_test
                      day10_common
                      gtest_main
                      common)

gtest_discover_tests(day10_test)
