#ifndef MERGEABLE_HEAPS_TEST_CASE_H
#define MERGEABLE_HEAPS_TEST_CASE_H

#include "test_action.h"

class TestCase : public ::testing::Test {
protected:
    void SetUp() override {
        actions_.resize(ACTIONS_CNT);
        int heaps_cnt = 0;
        for (auto &i: actions_) {
            i = TestAction(heaps_cnt);
            heaps_cnt += i.call == Func::AddHeap;
        }
    }

    void TearDown() override {}

    static const int ACTIONS_CNT = 100'000;
    std::vector<TestAction> actions_;
};

#endif // MERGEABLE_HEAPS_TEST_CASE_H
