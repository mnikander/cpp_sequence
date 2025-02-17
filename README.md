# Sequence library

This library generates a sequence of values and performs arbitrary transformations on that sequence.
The goal is to create a small library of composeable algorithms, including map, filter, reduce, and several other algorithms.
These algorithms should be easy use and easy to compose.
The resulting code should have only a small runtime overhead compared to the equivalent hand-crafted code.
Another goal is to avoid some of the pitfalls of the C++ ranges library, such as the 'terrible problem of incrementing a smart iterator'.

A variety of possible approaches have been explored.
The current approach builds a pipeline out of stages.
There are three building blocks from which a pipeline is built:
- a generator stage creates values and passes them onwards
- a stage receives values, transforms them, and passes them onwards, possibly to other intermediate stages
- a sink receives values and writes them into a container or result field

This workflow is heavily inspired by the sequences and streams libraries in Kotlin, as well as the 'Rappel' library presented at CppNow 2024 ([youtube](https://www.youtube.com/watch?v=itnyR9j8y6E)).

## Getting started

1. Install dependencies
```bash
sudo apt get install g++ cmake libgtest-dev
```

2. Clone the repo
```bash
git clone #...
cd #... navigate into the freshly cloned repo
```

3. Build and run:
```bash
mkdir out && cd out && cmake .. && cd .. # out-of-source build
cmake --build out/ && ./out/unit_tests
```

## Goals

1. The following shall be valid code: `from(vec) | filter(isEven) | take(3) | to(outputVec);`
2. After substitution of the templates, the code should be very similar to a handcrafted for-loop for this example, so that very little runtime overhead is introduced.
3. By extension, the generated assembly code should be very similar to that of the handcrafted for-loop.

## Design

How can pipelines of STL algorithms be decomposed? What sorts of operations are there?
- the elements (iterators, counters, generators)
- access pattern (iteration, strided access, binary search)
- iteration begin
- iteration end (end of range, count, or reached sentinel)
- skip elements (filter)
- modify iteration bounds (take, drop)
- early stopping criterion (predicate)
- transform elements (map)
- return value: accumulator, iterator, index, output range
- process one or more sequences (zip)
- how many elements to process (single element, adjacent elements)
- reorder input sequence (gather, scatter, rotate, reverse, sort, nth_element, permutation)

### Handling intermediate results

There are several ways in which the stages of the pipeline can handle data:

1. Stages receive all their inputs from the prior stage, including for example the accumulator value from the last iteration for left fold
2. State is stored in a meta-data object which is passed through the pipeline (how do stages decorate the meta-data with additional fields though? I think this would make the design really complicated.)
3. Stages hold their own data as member variables

To assist the compiler in better optimizing the code, and to make it easier to reason about the code, I would _like_ to have all function objects be referentially transparent.
Unfortunately, there are at least two function objects (`to` and `fold_left`) which make use of mutable state.
Perhaps it's easiest and best to hold the accumulator right where the algorithm is defined, as a member variable.
I'm not sure if `to` can be made referentially transparent at all, without making needless copies of the container.
I think #3 is the easiest to implement, and has the best separation of concerns between the stages.

### Outputting the final result

There are two ways the results of a pipeline can be handled:
1. Return the result
2. Continuation-passing style (CPS), where nothing ever returns, and the final result is written somewhere

Note that CPS may be able to model `filter` in a zero-overhead way, but output is a little more difficult since I would always need something similar to the `to` function object, even for the output of individual result values.
Since the C++ standard does not guarantee the tail-call optimization, I am concerned I may have performance problems with loops, or nested loops, if I implement the whole thing with CPS.
