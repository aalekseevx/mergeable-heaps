#include <gtest/gtest.h>
#include "test_case.h"
#include "test_action.h"
#include "mergeable_heaps/binomial.h"
#include "mergeable_heaps/leftist.h"
#include "mergeable_heaps/skew.h"
#include "naive_heap.h"

template<typename T>
void TestHeap(const std::vector<TestAction> &actions) {
    std::vector<T> candidate_heaps;
    std::vector<heaps::StlHeap<int>> correct_heaps;
    std::vector<size_t> sizes;
    for (auto action: actions) {
        RunAction<T>(candidate_heaps, correct_heaps, sizes, action);
    }
}

TEST_F(TestCase, BinomialHeapTest) {
    TestHeap<heaps::BinomialHeap<int>>(actions_);
}

TEST_F(TestCase, LeftistHeapTest) {
    TestHeap<heaps::LeftistHeap<int>>(actions_);
}

TEST_F(TestCase, SkewHeapTest) {
    TestHeap<heaps::SkewHeap<int>>(actions_);
}

TEST_F(TestCase, StlHeapTest) {
    TestHeap<heaps::StlHeap<int>>(actions_);
}