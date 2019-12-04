# Mergeable-heaps

[![Build Status](https://travis-ci.com/aalekseevx/Mergeable-heaps.svg?branch=master)](https://travis-ci.com/aalekseevx/Mergeable-heaps)

## Description

Implementation of [binomial heap](https://en.wikipedia.org/wiki/Binomial_heap),
[skew heap](https://en.wikipedia.org/wiki/Skew_heap), [leftist heap](https://en.wikipedia.org/wiki/Leftist_tree) in
C++. Developed as homework for DIHT Algorithms' and Data structures course.

## Build

### Prerequisites

The library requires

- g++6
- CMake 3.15

Building is nothing special.

```bash
    mkdir bin
    cd bin
    cmake ..
    make
```

## Running the tests

Tests are created with gtest framework. It will downloaded and compiled
during cmake. Run tests as follows:
```bash
    cd bin
    ctest
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.