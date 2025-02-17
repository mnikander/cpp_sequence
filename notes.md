# Design

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

## Handling intermediate results

There are several ways in which the stages of the pipeline can handle data:

1. Stages receive all their inputs from the prior stage, including for example the accumulator value from the last iteration for left fold
2. State is stored in a meta-data object which is passed through the pipeline (how do stages decorate the meta-data with additional fields though? I think this would make the design really complicated.)
3. Stages hold their own data as member variables

To assist the compiler in better optimizing the code, and to make it easier to reason about the code, I would _like_ to have all function objects be referentially transparent.
Unfortunately, there are at least two function objects (`to` and `fold_left`) which make use of mutable state.
Perhaps it's easiest and best to hold the accumulator right where the algorithm is defined, as a member variable.
I'm not sure if `to` can be made referentially transparent at all, without making needless copies of the container.
I think #3 is the easiest to implement, and has the best separation of concerns between the stages.

## Outputting the final result

There are two ways the results of a pipeline can be handled:
1. Return the result
2. Continuation-passing style (CPS), where nothing ever returns, and the final result is written somewhere

Note that CPS may be able to model `filter` in a zero-overhead way, but output is a little more difficult since I would always need something similar to the `to` function object, even for the output of individual result values.
Since the C++ standard does not guarantee the tail-call optimization, I am concerned I may have performance problems with loops, or nested loops, if I implement the whole thing with CPS.

## Improving the notation

Currently, a sequence must be assembled by hand, with a quite tedious notation.
The goal is to improve the notation significantly.
Given:
```c++
std::vector<int> const data{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
std::vector<int> result;
```
Suppose our goal is to obtain the first three even numbers from the data, i.e. `(0, 2, 4)`.
There are a few possible notations for how a pipeline could be defined and evaluated.

### Design option 1
Define and evaluate the pipeline in one go:
```c++
from(data) | filter(isEven) | take(3) | to(result);
```

### Design option 2
Separate the definition of the pipeline from its evaluation:
```c++
auto pipeline = from(data) | filter(isEven) | take(3) | to(result);
pipeline.run();
```

### Design option 3
Separate the definition of the pipeline from its evaluation, and use a function call to do it, to ensure that template parameters can be deduced correctly.
```c++
auto pipeline = build(from(data), filter(isEven), take(3), to(result));
pipeline.run();
```
