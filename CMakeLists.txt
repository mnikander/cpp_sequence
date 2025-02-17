cmake_minimum_required(VERSION 3.12)

project(cpp_sequence)

set(CMAKE_CXX_STANDARD 23)
add_compile_options(-g -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wfloat-conversion)

add_executable(continuation_find        deprecated/techniques/continuation_passing_style/find.cpp)
add_executable(continuation_plus_reduce deprecated/techniques/continuation_passing_style/plus_reduce.cpp)
add_executable(handcrafted_find         deprecated/techniques/handcrafted/find.cpp)
add_executable(handcrafted_plus_reduce  deprecated/techniques/handcrafted/plus_reduce.cpp)
add_executable(structured_copy_if       deprecated/techniques/structured_program/copy_if.cpp)
add_executable(structured_find          deprecated/techniques/structured_program/find.cpp)
add_executable(structured_map           deprecated/techniques/structured_program/map.cpp)
add_executable(structured_plus_reduce   deprecated/techniques/structured_program/plus_reduce.cpp)
add_executable(structured_zip           deprecated/techniques/structured_program/zip.cpp)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link unit_tests with what we want to test and the GTest and pthread library
add_executable(deprecated_v1_unit_tests
               deprecated/v1/test/test_compose.cpp
               deprecated/v1/test/test_fold_left.cpp
               deprecated/v1/test/test_from.cpp
               deprecated/v1/test/test_iterate.cpp
               deprecated/v1/test/test_select.cpp
               deprecated/v1/test/test_sequence.cpp
               deprecated/v1/test/test_to.cpp
               deprecated/v1/test/unit_testing_main.cpp
)
target_link_libraries(deprecated_v1_unit_tests ${GTEST_LIBRARIES} pthread)

add_executable(deprecated_v2_unit_tests ${SOURCES}
               deprecated/v2/test/test_find.cpp
               deprecated/v2/test/test_fold_left_if.cpp
               deprecated/v2/test/unit_testing_main.cpp
)
target_link_libraries(deprecated_v2_unit_tests ${GTEST_LIBRARIES} pthread)

add_executable(unit_tests ${SOURCES}
               test/main.test.cpp
               test/sequence.test.cpp
)
target_link_libraries(unit_tests ${GTEST_LIBRARIES} pthread)
