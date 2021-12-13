add_library(day13_common STATIC day13.cpp)

add_executable(day13_main
        day13_main.cpp)
target_link_libraries(day13_main
                      day13_common
                      common)

add_executable(day13_test
        day13_test.cpp)
target_link_libraries(day13_test
                      day13_common
                      gtest_main
                      common)

gtest_discover_tests(day13_test)
