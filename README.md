# Sequence library

This library generates a sequence of values and performs arbitrary transformations on that sequence.
The goal is to create a small library of composeable algorithms, including map, filter, reduce, and several other algorithms.
These algorithms should be easy use and easy to compose.
The resulting code should have only a small runtime overhead compared to the equivalent hand-crafted code.
Another goal is to avoid some of the pitfalls of the C++ ranges library, such as the 'terrible problem of incrementing a smart iterator'.

A variety of possible approaches have been explored.
The current approach builds a pipeline out of stages.
There are three building blocks from which a pipeline is built:
- a source creates values and passes them onwards
- a stage receives values, transforms them, and passes them onwards, possibly to other intermediate stages
- a sink receives values and writes them into a container or result field

This workflow is heavily inspired by the **Sequences** and **Streams** libraries in Kotlin, as well as the C++ **Rappel** library presented at CppNow 2024 ([youtube](https://www.youtube.com/watch?v=itnyR9j8y6E)).

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

## Usage examples

**Lots of usage examples can be found in the unit tests.**
We will take a detailed look at two examples here, to explain the basics, and to showcase some of the features.
The first example illustrates a pipeline where values are created using `iota`, are squared (i.e. x^2) using `map`, and the first 3 such values are taken and written to an output vector.

```cpp
using namespace seq;
std::vector<i64> const expected{0, 1, 4};
std::vector<i64> result{};
auto square = [](int value){ return value*value; };

// define the pipeline stages, from last to first
auto sink     = to_vector(result);         // write each result
auto take3    = take<int>(3, sink);        // HALT after 3 elements
auto map_sq   = map<int>(square, take3);   // square each element
auto sequence = from_iota(map_sq);         // generate integers [0, inf)

// run the pipeline until one of the stages signals HALT
sequence.run();

assert(result.size() == 3);
assert(result == expected);
```

Note that intermediate stages, such as `map` must explicitly specify the value type of their _inputs_, in this case `int`.
This allows any possible type mismatches to be identified by the compiler.
This ensures relatively short error messages, which clearly state _where_ in the pipeline the type mismatch occurred.

An example for a **map-filter-reduce** pipeline, common in functional programming languages, is given below.
Here, the pipeline stages are defined inline, from left-to-right, in the order in which they are executed.
Here, we use the function `yield(n)`, to execute the generator a fixed number of times.
The result may contain any number of values, depending on the pipeline.
In this case, where we are filtering for even numbers, the result will contain half as many elements as the generator yielded.

```cpp
using namespace seq;

auto minusThree = [](int i){ return i - 3; };
auto isEven     = [](int i){ return i % 2 == 0; };
int result = 0;

auto sequence =
    from_iota(
        map<int>(minusThree,
            filter<int>(isEven,
                reduce<int>(std::plus<int>{}, 0,
                    to_value(result)))));
sequence.yield(8); // sum of (-2, 0, 2, 4)
assert(result == 4);
```
Note that when we use `yield(n)`, execution will terminate after at most `n` iterations.
We don't _need_ to have a stage in the pipeline which signals HALT.
We can also call `yield(n)` multiple times to get more elements, and execution will continue, from where it left off, each time.
If any stage, for example a `take` or a `find` signals a HALT, however, the pipeline finishes the processing of the current element and then stops permanently.
In case of a halt, the pipeline cannot be restarted, and no further elements can be obtained via `yield(n)` or `run()`.

---
Copyright (c) 2024, Marco Nikander
