add_library(day15_common STATIC day15.cpp)

add_executable(day15_main
        day15_main.cpp)
target_link_libraries(day15_main
                      day15_common
                      common)

add_executable(day15_test
        day15_test.cpp)
target_link_libraries(day15_test
                      day15_common
                      gtest_main
                      common)

gtest_discover_tests(day15_test)
