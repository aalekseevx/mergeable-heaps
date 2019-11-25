#include <iostream>
#include <gtest/gtest.h>
#include "mergeable_heaps/binomial.h"
#include "mergeable_heaps/leftist.h"
#include "mergeable_heaps/skew.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}