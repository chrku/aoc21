add_library(day22_common STATIC day22.cpp)

add_executable(day22_main
        day22_main.cpp)
target_link_libraries(day22_main
                      day22_common
                      common)

add_executable(day22_test
        day22_test.cpp)
target_link_libraries(day22_test
                      day22_common
                      gtest_main
                      common)

gtest_discover_tests(day22_test)
