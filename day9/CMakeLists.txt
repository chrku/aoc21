add_library(day9_common STATIC day9.cpp)

add_executable(day9_main
        day9_main.cpp)
target_link_libraries(day9_main
                      day9_common
                      common)

add_executable(day9_test
        day9_test.cpp)
target_link_libraries(day9_test
                      day9_common
                      gtest_main
                      common)

gtest_discover_tests(day9_test)
