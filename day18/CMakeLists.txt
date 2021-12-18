add_library(day18_common STATIC day18.cpp)

add_executable(day18_main
        day18_main.cpp)
target_link_libraries(day18_main
                      day18_common
                      common)

add_executable(day18_test
        day18_test.cpp)
target_link_libraries(day18_test
                      day18_common
                      gtest_main
                      common)

gtest_discover_tests(day18_test)
