add_library(day4_common STATIC day4.cpp)

add_executable(day4_main
               day4_main.cpp)
target_link_libraries(day4_main
                      day4_common
                      common)

add_executable(day4_test
               day4_test.cpp)
target_link_libraries(day4_test
                      day4_common
                      gtest_main
                      common)

gtest_discover_tests(day4_test)
