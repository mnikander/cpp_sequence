#include <gtest/gtest.h>
#include "../src/sequence.hpp"

TEST(sequence, map)
{
    std::array<mut_i64, 5> result{0, 0, 0, 0, 0};
    std::array<mut_i64, 5> expected{0, 1, 4, 9, 16};

    auto f_id = [](auto emit, mut_i64 value)->void { emit(value); };
    auto f_sq = [](auto emit, mut_i64 value)->void { emit(value*value); };

    RangeSink sink{result};
    auto square = make_stage<mut_i64>(f_sq, sink);
    auto sequence = make_generator(f_id, square);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}
