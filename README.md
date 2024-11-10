# Structured programs via meta-programming

Can structured programs be generated at compile-time using templates?
Can such a structured program closely approximate the code from a handcrafted solution for a map-filter-reduce program?
What about for other linear algorithms in the STL?

If this is possible, then perhaps a small library of composeable algorithms could be created with this technique.

This is inspired by the 'Rappel' library presented at CppNow 2024 ([youtube](https://www.youtube.com/watch?v=itnyR9j8y6E)).

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
2. Find out if structured programms can be constructed by template meta-programming, to create such algorithm pipelines.
3. After substitution of the templates, the code should be very similar to a handcrafted for-loop for this example, so that very little runtime overhead is introduced.
4. By extension, the generated assembly code should be very similar to that of the handcrafted for-loop.

## Design

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
2. Continuation-passing style (CPS), where nothing ever returns

Note that CPS may be able to model `filter` in a zero-overhead way, but output is a little more difficult since I would always need something similar to the `to` function object, even for the output of single values.
Since the C++ standard does not guaranty the tail-call optimization, I am concerned I may have performance problems with loops, or nested loops, if I implement the whole thing with CPS.
Depending on how complicated the holding of intermediate state becomes, a solution based on CPS might actually be easier to implement.
