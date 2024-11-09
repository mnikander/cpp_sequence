cmake_minimum_required(VERSION 3.12)

project(cpp_meta_structured_programming)

set(CMAKE_CXX_STANDARD 23)

add_executable(handcrafted_accumulate samples/handcrafted/accumulate.cpp)
add_executable(cps_accumulate samples/continuation_passing_style/accumulate.cpp)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link unit_tests with what we want to test and the GTest and pthread library
add_executable(unit_tests ${SOURCES}
                          test/main.cpp
                          test/test_compose.cpp
                          test/test_fold_left.cpp
                          test/test_from.cpp
                          test/test_iterate.cpp
                          test/test_select.cpp
                          test/test_sequence.cpp
                          test/test_to.cpp
)
target_link_libraries(unit_tests ${GTEST_LIBRARIES} pthread)

