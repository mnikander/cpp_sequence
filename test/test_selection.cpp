#include <gtest/gtest.h>

#include "../src/example_functions.hpp"
#include "../src/selection.hpp"

TEST(select, nothing)
{
    using namespace sample;
    
    std::string const result = msp::select{less_than{0}, string_catenate{}, default_construct<std::string>{}}(0, std::string{""});

    EXPECT_EQ(result, "");
}
