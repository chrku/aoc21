add_library(day16_common STATIC day16.cpp)

add_executable(day16_main
        day16_main.cpp)
target_link_libraries(day16_main
                      day16_common
                      common)

add_executable(day16_test
        day16_test.cpp)
target_link_libraries(day16_test
                      day16_common
                      gtest_main
                      common)

gtest_discover_tests(day16_test)
