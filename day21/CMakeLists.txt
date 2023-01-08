add_library(day21_common STATIC day21.cpp)

add_executable(day21_main
        day21_main.cpp)
target_link_libraries(day21_main
                      day21_common
                      common)

add_executable(day21_test
        day21_test.cpp)
target_link_libraries(day21_test
                      day21_common
                      gtest_main
                      common)

gtest_discover_tests(day21_test)
