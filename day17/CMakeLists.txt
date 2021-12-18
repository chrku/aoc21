add_library(day17_common STATIC day17.cpp)

add_executable(day17_main
        day17_main.cpp)
target_link_libraries(day17_main
                      day17_common
                      common)

add_executable(day17_test
        day17_test.cpp)
target_link_libraries(day17_test
                      day17_common
                      gtest_main
                      common)

gtest_discover_tests(day17_test)
