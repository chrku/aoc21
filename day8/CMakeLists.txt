add_library(day8_common STATIC day8.cpp)

add_executable(day8_main
        day8_main.cpp)
target_link_libraries(day8_main
                      day8_common
                      common)

add_executable(day8_test
        day8_test.cpp)
target_link_libraries(day8_test
                      day8_common
                      gtest_main
                      common)

gtest_discover_tests(day8_test)
