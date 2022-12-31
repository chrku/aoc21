add_library(day20_common STATIC day20.cpp)

add_executable(day20_main
        day20_main.cpp)
target_link_libraries(day20_main
                      day20_common
                      common)

add_executable(day20_test
        day20_test.cpp)
target_link_libraries(day20_test
                      day20_common
                      gtest_main
                      common)

gtest_discover_tests(day20_test)
