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

The following example illustrates a pipeline where values are created using `iota`, are squared (i.e. x^2) using `map`, and then written to an output vector.

```cpp
using namespace seq;

std::vector<int> const expected{0, 1, 4, 9, 16};
std::vector<int> result{};
auto squared = [](int value){ return value*value; };

// pipeline stages, nested in order
auto pipeline = iota(map<int>(squared, toVector(result)));

// run the pipeline to produce the first 5 values
pipeline.yield(5);

assert(result.size() == 5);
assert(result == expected);
```

Note that intermediate stages, such as `map` must explicitly specify the value type of their _inputs_, in this case `int`.
This allows any possible type mismatches to be localized identified by the compiler.
This ensures relatively short error messages, which clearly state where in the pipeline the type mismatch occured.

An example for a **map-filter-reduce** pipeline, common in functional programming languages, is given below:

```cpp
using namespace seq;

auto minusThree = [](int i){ return i - 3; };
auto isEven     = [](int i){ return i % 2 == 0; };
int result = 0;

auto sequence =
    iota(
        map<int>(minusThree,
            filter<int>(isEven,
                reduce<int>(std::plus<int>{}, 0,
                    toValue(result)))));
sequence.yield(8); // sum of (-2, 0, 2, 4)
assert(result == 4);
```

---
Copyright (c) 2024, Marco Nikander
