#include <random>
#include <gtest/gtest.h>
#include "mergeable_heaps/binomial.h"
#include "mergeable_heaps/skew.h"
#include "mergeable_heaps/leftist.h"
#include "stl_naive.h"
#include "mergeable_heaps/exceptions.h"

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
        key = gen();
        if (heaps_cnt == 0) {
            call = Func::AddHeap;
            index[0] = index[1] = -1;
        } else {
            call = Func(static_cast<size_t>(gen()) % func_count);
            for (int &i: index) {
                i = static_cast<size_t>(gen()) % heaps_cnt;
            }
        }
    }
};

class TestCase : public ::testing::Test {
protected:
    void SetUp() override {
        actions_.resize(ACTIONS_CNT);
        int heaps_cnt = 0;
        for (auto &i: actions_) {
            i = Action(heaps_cnt);
            heaps_cnt += i.call == Func::AddHeap;
        }
    }

    void TearDown() override {}

    static const int ACTIONS_CNT = 10000;
    std::vector<Action> actions_;
};

template<class T, class H>
void TestAction(std::vector<T> &candidate_heaps,
                std::vector<H> &correct_heaps,
                std::vector<size_t> &sizes,
                Action action) {

    switch (action.call) {
        case Func::GetMinimum: {
            int candidate_answer = -1, correct_answer = -1;
            if (sizes[action.index[0]] > 0) {
                ASSERT_NO_THROW(candidate_answer = candidate_heaps[action.index[0]].GetMinimum());
                ASSERT_NO_THROW(correct_answer = correct_heaps[action.index[0]].GetMinimum());
                ASSERT_EQ(candidate_answer, correct_answer);
            } else {
                ASSERT_THROW(candidate_answer = candidate_heaps[action.index[0]].GetMinimum(), heaps::EmptyHeapException);
                ASSERT_THROW(correct_answer = correct_heaps[action.index[0]].GetMinimum(), heaps::EmptyHeapException);
            }
            break;
        }
        case Func::AddHeap: {
            ASSERT_NO_THROW(candidate_heaps.emplace_back(action.key));
            ASSERT_NO_THROW(correct_heaps.emplace_back(action.key));
            sizes.emplace_back(1);
            break;
        }
        case Func::ExtractMinimum: {
            if (sizes[action.index[0]] > 0) {
                ASSERT_NO_THROW(candidate_heaps[action.index[0]].ExtractMinimum());
                ASSERT_NO_THROW(correct_heaps[action.index[0]].ExtractMinimum());
                --sizes[action.index[0]];
            } else {
                ASSERT_THROW(candidate_heaps[action.index[0]].ExtractMinimum(), heaps::EmptyHeapException);
                ASSERT_THROW(correct_heaps[action.index[0]].ExtractMinimum(), heaps::EmptyHeapException);
            }
            break;
        }
        case Func::Insert: {
            ASSERT_NO_THROW(candidate_heaps[action.index[0]].Insert(action.key));
            ASSERT_NO_THROW(correct_heaps[action.index[0]].Insert(action.key));
            ++sizes[action.index[0]];
            break;
        }
        case Func::Merge: {
            if (action.index[0] != action.index[1]) {
                ASSERT_NO_THROW(candidate_heaps[action.index[0]].Merge(candidate_heaps[action.index[1]]));
                ASSERT_NO_THROW(correct_heaps[action.index[0]].Merge(correct_heaps[action.index[1]]));
                sizes[action.index[0]] += sizes[action.index[1]];
                sizes[action.index[1]] = 0;
            } else {
                ASSERT_THROW(candidate_heaps[action.index[0]].Merge(candidate_heaps[action.index[1]]), heaps::SelfHeapMerge);
                ASSERT_THROW(correct_heaps[action.index[0]].Merge(correct_heaps[action.index[1]]), heaps::SelfHeapMerge);
            }
            break;
        }
    }
}

template<typename T>
void TestHeap(const std::vector<Action> &actions) {
    std::vector<T> candidate_heaps;
    std::vector<heaps::StlHeap<int>> correct_heaps;
    std::vector<size_t> sizes;
    for (auto action: actions) {
        TestAction<T>(candidate_heaps, correct_heaps, sizes, action);
    }
}

//TEST_F(TestCase, BinomialHeapTest) {
//    TestHeap<heaps::BinomialHeap<int>>(actions_);
//}
//
//TEST_F(TestCase, LeftistHeapTest) {
//    TestHeap<heaps::LeftistHeap<int>>(actions_);
//}

TEST_F(TestCase, SkewHeapTest) {
    TestHeap<heaps::SkewHeap<int>>(actions_);
}

TEST_F(TestCase, StlHeapTest) {
    TestHeap<heaps::StlHeap<int>>(actions_);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}