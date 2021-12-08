add_library(day5_common STATIC day5.cpp)

add_executable(day5_main
        day5_main.cpp)
target_link_libraries(day5_main
                      day5_common
                      common)

add_executable(day5_test
        day5_test.cpp)
target_link_libraries(day5_test
                      day5_common
                      gtest_main
                      common)

gtest_discover_tests(day5_test)
