add_library(day19_common STATIC day19.cpp)

add_executable(day19_main
        day19_main.cpp)
target_link_libraries(day19_main
                      day19_common
                      common)

add_executable(day19_test
        day19_test.cpp)
target_link_libraries(day19_test
                      day19_common
                      gtest_main
                      common)

gtest_discover_tests(day19_test)
