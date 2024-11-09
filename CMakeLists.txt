cmake_minimum_required(VERSION 3.12)

project(cpp_meta_structured_programming)

set(CMAKE_CXX_STANDARD 23)

add_executable(continuation_find        samples/continuation_passing_style/find.cpp)
add_executable(continuation_plus_reduce samples/continuation_passing_style/plus_reduce.cpp)
add_executable(handcrafted_find         samples/handcrafted/find.cpp)
add_executable(handcrafted_plus_reduce  samples/handcrafted/plus_reduce.cpp)
add_executable(structured_plus_reduce   samples/structured_program/plus_reduce.cpp)
add_executable(structured_find          samples/structured_program/find.cpp)
add_executable(structured_map           samples/structured_program/map.cpp)

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
