# Sequence library

This library generates a sequence of values and performs arbitrary transformations on that sequence.
The goal is to create a small library of composeable algorithms, including map, filter, reduce, and several other algorithms.
These algorithms should be easy use and easy to compose.
The resulting code should have only a small runtime overhead compared to the equivalent hand-crafted code.
Another goal is to avoid some of the pitfalls of the C++ ranges library, such as the 'terrible problem of incrementing a smart iterator'.

A variety of possible approaches have been explored.
The current approach builds a pipeline out of stages.
There are three building blocks from which a pipeline is built:
- a generator creates values and passes them onwards
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
