add_library(day2_common STATIC day2.cpp)

add_executable(day2_main
               day2_main.cpp)
target_link_libraries(day2_main
                      day2_common
                      common)

add_executable(day2_test
               day2_test.cpp)
target_link_libraries(day2_test
                      day2_common
                      gtest_main
                      common)

gtest_discover_tests(day2_test)
