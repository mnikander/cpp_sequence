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
    
    auto              f      = msp::select{less_than{0}, to_string{}, default_construct<std::string>{}};
    std::string const result = f(0, ' ');

    EXPECT_EQ(result, "");
}

TEST(select, one)
{
    using namespace sample;

    auto              f      = msp::select{counter_equal_to{1}, to_string{}, default_construct<std::string>{}};
    std::string const result = f(1, 42);

    EXPECT_EQ(result, std::string("42"));
}

TEST(select, container)
{
    using namespace sample;

    std::vector<int> const vec{13, 26, 42};

    // we are going to build a function similar to:
    // auto f = [](int i){ return (vec[i] == 42) ? std::string("Yes") : std::string("No"); };

    auto              getter  = get{vec};
    auto              answer  = constant{42};
    auto              glue    = std::equal_to<int>{};
    auto              yea     = constant{std::string("Yes")};
    auto              nay     = constant{std::string("No")};
    auto              f       = msp::select{msp::sequence(glue, getter, answer), yea, nay};
    std::string const result0 = f(0, 0);
    std::string const result1 = f(1, 0);
    std::string const result2 = f(2, 0);

    EXPECT_EQ(result0, std::string("No"));
    EXPECT_EQ(result1, std::string("No"));
    EXPECT_EQ(result2, std::string("Yes"));
}

TEST(select, recursive)
{
    using namespace sample;

    std::string const s1 = "one";
    std::string const s2 = "two";
    std::string const s3 = "other";

    auto f = msp::select(counter_equal_to{1},
                            constant{s1},
                            msp::select(counter_equal_to{2},
                                constant{s2},
                                constant{s3}));

    EXPECT_EQ(f(1, std::string{}), s1);
    EXPECT_EQ(f(2, std::string{}), s2);
    EXPECT_EQ(f(3, std::string{}), s3);
}
