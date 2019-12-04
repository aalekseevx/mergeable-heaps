# Mergeable heaps

[![Build Status](https://travis-ci.com/aalekseevx/Mergeable-heaps.svg?branch=master)](https://travis-ci.com/aalekseevx/Mergeable-heaps)

## Description

Implementation of [binomial heap](https://en.wikipedia.org/wiki/Binomial_heap),
[skew heap](https://en.wikipedia.org/wiki/Skew_heap), [leftist heap](https://en.wikipedia.org/wiki/Leftist_tree) in
C++. Developed as homework for DIHT Algorithms' and Data structures course.

## Build

### Prerequisites

The library requires

- g++6 or clang 11
- CMake 3.15

Building is nothing special.

```bash
    mkdir bin
    cd bin
    cmake ..
    make
```

## Running the tests

Tests are created with [google test](https://github.com/google/googletest/) framework. It will be downloaded and compiled
during cmake. Run tests as follows:
```bash
    ./bin/RunUnitTests
```

## Usage

Learn by example:

```cpp
#include "mergeable_heaps/binomial.h"
#include <cassert>

int main() 
    heaps::BinomialHeap<double> first_heap, second_heap(2.71);
    // Or with the same result:
    // heaps::SkewHeap<double> first_heap, second_heap(2.71);
    // heaps::LeftistHeap<double> first_heap, second_heap(2.71);


    first_heap.Insert(3.14);
    second_heap.Insert(second_heap.GetMinimum() * 2.0); // inserting 5.42

    first_heap.Merge(second_heap); // Merging heaps

    assert(first_heap.Size() == 3); // first heap contains { 2.71, 3.14, 5.42 }
    assert(second_heap.Empty()); // second heap was merged to 1st, so empty
    assert(first_heap.GetMinimum() == 2.71);

    first_heap.ExtractMinimum(); // extracting 2.71
    first_heap.ExtractMinimum(); // extracting 3.14

    assert(first_heap.GetMinimum() == 5.42);

    return 0;
}
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.