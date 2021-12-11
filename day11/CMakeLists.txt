add_library(day11_common STATIC day11.cpp)

add_executable(day11_main
        day11_main.cpp)
target_link_libraries(day11_main
                      day11_common
                      common)

add_executable(day11_test
        day11_test.cpp)
target_link_libraries(day11_test
                      day11_common
                      gtest_main
                      common)

gtest_discover_tests(day11_test)
