// Copyright (c) 2025, Marco Nikander

#include <vector>
#include <gtest/gtest.h>
#include "../../src/prototype_stage/concept_iota.hpp"
#include "../../src/prototype_stage/concept_take.hpp"
#include "../../src/prototype_stage/concept_vector.hpp"
#include "../../src/datatypes.hpp"
// #include "../../src/stage/filter_stage.hpp"
// #include "../../src/stage/map_stage.hpp"


TEST(prototype_concept_take, zero)
{
    using namespace seq;
    std::vector<i64> result{};

    // pipeline stages, from last to first
    auto sink     = toVectorConcept(result);
    auto take0    = takeConcept<i64>(0, sink);
    auto sequence = iotaConcept(take0);
    run(sequence);
    EXPECT_EQ(result.size(), 0);
}

TEST(prototype_concept_take, one)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0};

    // pipeline stages, from last to first
    auto sink     = toVectorConcept(result);
    auto take1    = takeConcept<i64>(1, sink);
    auto sequence = iotaConcept(take1);
    run(sequence);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result, expected);
}

TEST(prototype_concept_take, two)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 1};

    // pipeline stages, from last to first
    auto sink     = toVectorConcept(result);
    auto take2    = takeConcept<i64>(2, sink);
    auto sequence = iotaConcept(take2);
    run(sequence);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result, expected);
}

TEST(prototype_concept_take, five)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 1, 2, 3, 4};

    // pipeline stages, from last to first
    auto sink     = toVectorConcept(result);
    auto take5    = takeConcept<i64>(5, sink);
    auto sequence = iotaConcept(take5);
    run(sequence);
    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result, expected);
}

TEST(prototype_concept_take, halt_and_attempt_restart)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 1};

    // pipeline stages, from last to first
    auto sink     = toVectorConcept(result);
    auto take2    = takeConcept<i64>(2, sink);
    auto sequence = iotaConcept(take2);
    run(sequence); // get 2 values
    run(sequence); // attempt to restart the pipeline: it should NOT start
    yield(sequence, 2); // attempt to restart via yield: it should NOT start
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result, expected);
}

// TEST(prototype_concept_take, map_three_numbers)
// {
//     using namespace seq;
//     std::vector<i64> const expected{0, 1, 4};
//     std::vector<i64> result{};
//     auto square = [](int value){ return value*value; };

//     // define the pipeline stages, from last to first
//     auto sink     = toVectorConcept(result);          // write each result
//     auto take3    = takeConcept<int>(3, sink);        // HALT after 3 elements
//     auto map_sq   = map<int>(square, take3);   // square each element
//     auto sequence = iotaConcept(map_sq);              // generate integers [0, inf)

//     // run the pipeline until one of the stages signals HALT
//     run(sequence);
//     EXPECT_EQ(result.size(), 3);
//     EXPECT_EQ(result, expected);
// }

// TEST(prototype_concept_take, three_even_numbers)
// {
//     using namespace seq;
//     std::vector<i64> result{};
//     std::vector<i64> const expected{0, 2, 4};
//     auto isEven = [](i64 i) {return i % 2 == 0; };

//     // pipeline stages, from last to first
//     auto sink     = toVector(result);
//     auto take3    = takeConcept<i64>(3, sink);
//     auto filterEv = filter<i64>(isEven, take3);
//     auto sequence = iota(filterEv);
//     run(sequence);
//     EXPECT_EQ(result.size(), 3);
//     EXPECT_EQ(result, expected);
// }

// TEST(prototype_concept_take, nested_call)
// {
//     using namespace seq;
//     std::vector<i64> result{};
//     std::vector<i64> const expected{0, 2, 4};
//     auto isEven = [](i64 i) {return i % 2 == 0; };

//     // pipeline, nested in order
//     auto sequence =
//         iota(
//             filter<i64>(isEven,
//                 takeConcept<i64>(3,
//                     toVector(result))));
//     run(sequence);
//     EXPECT_EQ(result.size(), 3);
//     EXPECT_EQ(result, expected);
// }
