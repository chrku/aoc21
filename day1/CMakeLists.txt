add_library(day1_common STATIC day11.cpp)

add_executable(day1_main
               day1_main.cpp)
target_link_libraries(day1_main
                      day1_common
                      common)

add_executable(day1_test
               day1_test.cpp)
target_link_libraries(day1_test
                      day1_common
                      gtest_main
                      common)

gtest_discover_tests(day1_test)
