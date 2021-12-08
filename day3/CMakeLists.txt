add_library(day3_common STATIC day3.cpp)

add_executable(day3_main
               day3_main.cpp)
target_link_libraries(day3_main
                      day3_common
                      common)

add_executable(day3_test
               day3_test.cpp)
target_link_libraries(day3_test
                      day3_common
                      gtest_main
                      common)

gtest_discover_tests(day3_test)
