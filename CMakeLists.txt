cmake_minimum_required(VERSION 3.12)

project(cpp_meta_structured_programming)

set(CMAKE_CXX_STANDARD 23)
add_compile_options(-g -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wfloat-conversion)

add_executable(continuation_find        samples/continuation_passing_style/find.cpp)
add_executable(continuation_plus_reduce samples/continuation_passing_style/plus_reduce.cpp)
add_executable(handcrafted_find         samples/handcrafted/find.cpp)
add_executable(handcrafted_plus_reduce  samples/handcrafted/plus_reduce.cpp)
add_executable(structured_copy_if       samples/structured_program/copy_if.cpp)
add_executable(structured_find          samples/structured_program/find.cpp)
add_executable(structured_map           samples/structured_program/map.cpp)
add_executable(structured_plus_reduce   samples/structured_program/plus_reduce.cpp)
add_executable(structured_zip           samples/structured_program/zip.cpp)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link unit_tests with what we want to test and the GTest and pthread library
add_executable(deprecated_unit_tests
               deprecated/test/test_compose.cpp
               deprecated/test/test_fold_left.cpp
               deprecated/test/test_from.cpp
               deprecated/test/test_iterate.cpp
               deprecated/test/test_select.cpp
               deprecated/test/test_sequence.cpp
               deprecated/test/test_to.cpp
               deprecated/test/unit_testing_main.cpp
)
target_link_libraries(deprecated_unit_tests ${GTEST_LIBRARIES} pthread)

add_executable(deprecated_v2_unit_tests ${SOURCES}
               deprecated_v2/test/test_find.cpp
               deprecated_v2/test/test_fold_left_if.cpp
               deprecated_v2/test/unit_testing_main.cpp
)
target_link_libraries(deprecated_v2_unit_tests ${GTEST_LIBRARIES} pthread)

add_executable(unit_tests ${SOURCES}
               test/test_sequence.cpp
               test/unit_testing_main.cpp
)
target_link_libraries(unit_tests ${GTEST_LIBRARIES} pthread)
