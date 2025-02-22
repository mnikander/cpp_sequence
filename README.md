# Sequence library

This library allows creating and transforming sequences of values, and doing computations on them.
The goal is to create a small and simple library of composeable algorithms, including map, filter, reduce, and several other algorithms.
These algorithms should be easy use and easy to compose.
If something is put together incorrectly, the error messages should be human-readable (and not pages and pages of template errors).
Aspirationally, the resulting code should have only a small runtime overhead compared to the equivalent hand-crafted code.
It is also hoped that some of the pitfalls of the C++ ranges library, such as the '[terrible problem of incrementing a smart iterator](https://www.fluentcpp.com/2019/02/12/the-terrible-problem-of-incrementing-a-smart-iterator/)', can be avoided by using generators instead of iterators.

Overall, a variety of possible approaches were explored.
This implementation is based on [continuation-passing style](https://en.wikipedia.org/wiki/Continuation-passing_style), and is heavily inspired by the **Sequences** and **Streams** libraries in Kotlin, as well as the C++ **Rappel** library presented at C++Now 2024 ([youtube](https://www.youtube.com/watch?v=itnyR9j8y6E)).

## How does it work?
There are three building blocks from which a pipeline is built:
- a **source** creates values one at a time, and passes them onwards
- a **stage** receives a value, does something with it, and (usually) passes the result onwards
- a **sink** receives values and writes them into a container or result variable

Each stage has a member function `receive(value)`.
Sinks also have this function.
Each stage has a member variable called `_successor`, which is the next stage in the pipeline.
To run the pipeline, each stage does what it has to do, and if it has a result it wants to push into the next stage, it calls `_successor.receive(result);`.
This passes the intermediate result onwards, and executes the next stage on that value.
Here is a simplified implementation of 'receive' for a [map](https://en.wikipedia.org/wiki/Map_(higher-order_function)) stage:
```cpp
void receive(value) {
    _successor.receive(func(value));
}
```
where `func` is a unary function which was specified when the stage was created.
This could be the square root function, for example.
As a second example, here is a simplified implementation of 'receive' for a [filter](https://en.wikipedia.org/wiki/Filter_(higher-order_function)) stage:
```cpp
void receive(value) {
    if(func(value)) {
        _successor.receive(value);
    }
}
```
where `func` is a function which returns `true` if the value should be passed onwards, and `false` otherwise.
An example could be a function which checks whether or not a number is positive.
Note that a _filter_ passes values forward _if and only if_ that value matches the filter.
Otherwise, the following stages are not even executed -- so we are not wasting any CPU cycles. ;)

At the end of a pipeline, a sink receives the result and writes it to some sort of output variable or container.

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
This is mandatory, the pipeline will not compile if the input type of a stage is missing.

An example for a **map-filter-reduce** pipeline, common in functional programming languages, is given below.
Here, the pipeline stages are defined inline, from left-to-right, in the order in which they are executed.
Instead of `run()`, we use the function `yield(n)` to execute the generator a fixed number of times.
The result may contain any number of values, depending on the pipeline.
In this case, where we are filtering for even numbers, so the result will contain half as many elements as the generator yielded.

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
We can also call `yield(n)` multiple times to get more elements, and execution will continue from where it left off, each time.
If any stage, for example a `take` or a `find` signals a HALT, however, the pipeline finishes the processing of the current element and then stops permanently.
In case of a HALT, the pipeline cannot be restarted, and no further elements can be obtained via `yield(n)` or `run()`.

---
Copyright (c) 2024, Marco Nikander
