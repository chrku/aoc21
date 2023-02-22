add_library(day23_common STATIC day23.cpp)

add_executable(day23_main
        day23_main.cpp)
target_link_libraries(day23_main
                      day23_common
                      common)

add_executable(day23_test
        day23_test.cpp)
target_link_libraries(day23_test
                      day23_common
                      gtest_main
                      common)

gtest_discover_tests(day23_test)
