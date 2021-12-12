add_library(day12_common STATIC day12.cpp)

add_executable(day12_main
        day12_main.cpp)
target_link_libraries(day12_main
                      day12_common
                      common)

add_executable(day12_test
        day12_test.cpp)
target_link_libraries(day12_test
                      day12_common
                      gtest_main
                      common)

gtest_discover_tests(day12_test)
