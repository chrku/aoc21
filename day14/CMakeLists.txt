add_library(day14_common STATIC day14.cpp)

add_executable(day14_main
        day14_main.cpp)
target_link_libraries(day14_main
                      day14_common
                      common)

add_executable(day14_test
        day14_test.cpp)
target_link_libraries(day14_test
                      day14_common
                      gtest_main
                      common)

gtest_discover_tests(day14_test)
