#include <iostream>
#include <random>
#include <gtest/gtest.h>
#include "mergeable_heaps/binomial.h"
#include "mergeable_heaps/leftist.h"
#include "mergeable_heaps/skew.h"
#include "stl_naive.h"

enum Func {
    AddHeap, Insert, GetMinimum, ExtractMinimum, Merge
};

class Action {
public:
    constexpr static const int func_count = 5;
    Func call;
    int key;
    int index[2];
    Action() = default;
    Action(size_t heaps_cnt) {
        static std::mt19937 gen;
        if (heaps_cnt == 0) {
            call = Func::AddHeap;
        } else {
            call = Func(static_cast<size_t>(gen()) % func_count);
            key = gen();
            for(int& i: index) {
                i = static_cast<size_t>(gen()) % heaps_cnt;
            }
        }
    }
};

class TestCase: public ::testing::Test {
protected:
    void SetUp() override {
        actions_.resize(ACTIONS_CNT);
        int heaps_cnt = 0;
        for (auto& i: actions_) {
            i = Action(heaps_cnt);
            heaps_cnt += i.call == Func::AddHeap;
        }
    }
    void TearDown() override {}
    static const int ACTIONS_CNT = 10'000;
    std::vector<Action> actions_;
};

template <class T>
void TestAction (heaps::IHeap<T>& candidate, heaps::IHeap<T>& correct, Action action) {

}

template <typename T> void TestHeap(const std::vector<Action>& actions_) {
    std::vector<T> candidate_heaps;
    std::vector<heaps::StlHeap<int>> correct_heaps;
    for (auto action: actions_) {
        if (action.call == Func::GetMinimum) {
            int candidate_answer = -1, correct_answer = -1;
            ASSERT_NO_THROW(candidate_answer = candidate_heaps[action.index[0]].GetMinimum());
            ASSERT_NO_THROW(correct_answer = correct_heaps[action.index[1]].GetMinimum());
            ASSERT_EQ(candidate_answer, correct_answer);
        } else if (action.call == Func::AddHeap) {
            ASSERT_NO_THROW(candidate_heaps.emplace_back());
            ASSERT_NO_THROW(correct_heaps.emplace_back());
        } else if (action.call == Func::ExtractMinimum) {
            ASSERT_NO_THROW(candidate_heaps[action.index[0]].ExtractMinimum());
            ASSERT_NO_THROW(correct_heaps[action.index[1]].ExtractMinimum());
        } else if (action.call == Func::Insert) {
            ASSERT_NO_THROW(candidate_heaps[action.index[0]].Insert(action.key));
            ASSERT_NO_THROW(correct_heaps[action.index[0]].Insert(action.key));
        } else if (action.call == Func::Merge) {
            ASSERT_NO_THROW(candidate_heaps[action.index[0]].Merge(candidate_heaps[action.index[1]]));
            ASSERT_NO_THROW(correct_heaps[action.index[0]].Merge(correct_heaps[action.index[1]]));
        }
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


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}