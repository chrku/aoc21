add_library(day25_common STATIC day25.cpp)

add_executable(day25_main
        day25_main.cpp)
target_link_libraries(day25_main
                      day25_common
                      common)

add_executable(day25_test
        day25_test.cpp)
target_link_libraries(day25_test
                      day25_common
                      gtest_main
                      common)

gtest_discover_tests(day25_test)
