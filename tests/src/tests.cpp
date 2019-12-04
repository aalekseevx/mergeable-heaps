#include <gtest/gtest.h>
#include "test_case.h"
#include "test_action.h"
#include "mergeable_heaps/binomial_heap.h"
#include "mergeable_heaps/leftist_heap.h"
#include "mergeable_heaps/skew_heap.h"
#include "naive_heap.h"
#include "simple_key.h"

template<typename T>
void TestHeap(const std::vector<TestAction> &actions) {
    std::vector<T> candidate_heaps;
    std::vector<heaps::StlHeap<SimpleKey>> correct_heaps;
    std::vector<size_t> sizes;
    for (auto action: actions) {
        RunAction<T>(candidate_heaps, correct_heaps, sizes, action);
    }
}

TEST_F(TestCase, BinomialHeapTest) {
    TestHeap<heaps::BinomialHeap<SimpleKey>>(actions_);
}

TEST_F(TestCase, LeftistHeapTest) {
    TestHeap<heaps::LeftistHeap<SimpleKey>>(actions_);
}

TEST_F(TestCase, SkewHeapTest) {
    TestHeap<heaps::SkewHeap<SimpleKey>>(actions_);
}

TEST_F(TestCase, StlHeapTest) {
    TestHeap<heaps::StlHeap<SimpleKey>>(actions_);
}