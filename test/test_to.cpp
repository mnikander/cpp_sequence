#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "../src/algorithm/to.hpp"

TEST(to, one)
{
    std::vector<std::string> output_vector{"0"};

    auto       f      = msp::to{output_vector};
    auto const result = f(0, std::string{"hello world"});

    EXPECT_EQ(output_vector[0], std::string{"hello world"});
}
