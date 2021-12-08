add_library(day6_common STATIC day6.cpp)

add_executable(day6_main
               day6_main.cpp)
target_link_libraries(day6_main
                      day6_common
                      common)

add_executable(day6_test
               day6_test.cpp)
target_link_libraries(day6_test
                      day6_common
                      gtest_main
                      common)

gtest_discover_tests(day6_test)
