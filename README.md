
# Sequence Library

**Efficient, composable, and easy-to-use pipelines for sequence processing in C++.**

This library provides a lightweight and expressive way to process sequences of values using functional programming concepts. Inspired by Kotlin Sequences and the C++ [Rappel](https://www.youtube.com/watch?v=itnyR9j8y6E) library, it enables the creation of **clear, efficient, and easily composable data transformations**.

## Features

- **Composable Functional Pipelines** – Chain `map`, `filter`, `reduce`, and more
- **Readable Compile-Time Errors** – Short, clear error messages for easier debugging
- **Avoids Iterator Pitfalls** – Uses generators instead of iterators to sidestep C++ iterator complexities
- **Optimized for Performance** – Avoids unnecessary allocations and function calls

## Quick Example

Before diving into details, here’s a simple example demonstrating how to create and run a sequence pipeline:

```cpp
#include "src/sequence.hpp"
using namespace seq;

std::vector<int> result;

auto pipeline = from_iota(
    map<int>([](int x) { return x * x; },
        take<int>(3,
            to_vector(result))));

pipeline.run(); // Generates {0, 1, 4}
```

This pipeline:

1. Generates integers from `0` onwards (`from_iota`)
2. Squares each value (`map`)
3. Takes the first 3 values (`take`)
4. Collects them in `result` (`to_vector`)

---

## Installation & Setup

### **1. Install Dependencies**

```bash
sudo apt install g++ cmake libgtest-dev libbenchmark-dev
```

### **2. Clone the Repository**

```bash
git clone git@github.com:mnikander/cpp_sequence.git
cd cpp_sequence
```

### **3. Build and Run Tests**

```bash
mkdir out && cd out && cmake .. && cd ..
cmake --build out/ && ./out/unit_tests
```

---

## How It Works

This library models a **pipeline** using three building blocks:

- **Source** – Generates values (`from_iota`, `from_vector`, etc.)
- **Stage** – Transforms values (`map`, `filter`, `take`, `reduce`, etc.)
- **Sink** – Collects results (`to_vector`, `to_value`, etc.)

A sequence processes values individually, pushing them through the stages step by step.

### Example: **Map-Filter-Reduce Pipeline**

```cpp
#include "src/sequence.hpp"
using namespace seq;

int result = 0;

auto pipeline = from_iota(
    map<int>([](int i) { return i - 3; },
        filter<int>([](int i) { return i % 2 == 0; },
            reduce<int>(std::plus<int>{}, 0,
                to_value(result)))));

pipeline.yield(8); // Process first 8 elements, filtering evens
assert(result == 4); // Sum of (-2, 0, 2, 4)
```
Each stage in the pipeline _must_ explicitly specify its input type (e.g., `map<int>`, `filter<int>`).
This ensures simple compile-time type checking and results in clear, readable error messages, preventing template-related confusion.
Many more usage examples can be found in the [unit tests](https://github.com/mnikander/cpp_sequence/tree/main/test)!
> Note: forgetting to specify the input type of stage is a common cause of errors such as _"no instance of function template 'reduce' matches the argument list"_.

### **Why Not Just Use `std::ranges`?**

While `std::ranges` provides powerful sequence transformations, this library offers:

- **Generator-based execution** – Avoids [complex iterator issues](https://www.fluentcpp.com/2019/02/12/the-terrible-problem-of-incrementing-a-smart-iterator/)
- **More readable error messages** – Explicit input types prevent cryptic template errors
- **Minimal boilerplate** – Easily chainable and more intuitive syntax

If you’re looking for a **simple alternative to iterators** with **clear syntax and minimal boilerplate**, this library is a good fit!

---

**Copyright (c) 2024, Marco Nikander**
