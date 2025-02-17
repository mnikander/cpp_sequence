#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "../src/algorithm/to.hpp"

TEST(to, one)
{
    using namespace msp;
    
    std::vector<std::string> output_vector{"0"};

    auto       f      = to{output_vector};
    auto const result = f(0, std::string{"hello world"});
    (void)result; // the returned value is not used, only the output vector

    EXPECT_EQ(output_vector[0], std::string{"hello world"});
}
