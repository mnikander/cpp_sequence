#include <gtest/gtest.h>
#include <functional>
#include <string>
#include <vector>

#include "../src/example_functions.hpp"
#include "../src/example_predicates.hpp"
#include "../src/select.hpp"
#include "../src/sequence.hpp"

TEST(select, nothing)
{
    using namespace sample;
    
    std::string const result = msp::select{less_than{0}, string_catenate{}, default_construct<std::string>{}}(0, std::string{""});

    EXPECT_EQ(result, "");
}

TEST(select, one)
{
    using namespace sample;

    std::string const result = msp::select{equal_to{1}, string_catenate{}, default_construct<std::string>{}}(1, std::string{""});

    EXPECT_EQ(result, "1 ");
}

TEST(select, container)
{
    using namespace sample;

    std::vector<int> const vec{13, 26, 42};

    auto getter               = get{vec};
    auto answer               = constant{42};
    auto glue                 = std::equal_to<int>{};
    auto yea                  = constant{std::string("Yes")};
    auto nay                  = constant{std::string("No")};
    auto const f              = msp::select{msp::sequence(glue, getter, answer), yea, nay};
    std::string const result0 = f(0, 0);
    std::string const result1 = f(1, 0);
    std::string const result2 = f(2, 0);

    EXPECT_EQ(result0, std::string("No"));
    EXPECT_EQ(result1, std::string("No"));
    EXPECT_EQ(result2, std::string("Yes"));
}
