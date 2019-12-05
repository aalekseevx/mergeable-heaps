#ifndef MERGEABLE_HEAPS_TEST_ACTION_H
#define MERGEABLE_HEAPS_TEST_ACTION_H

#include <random>
#include "gtest/gtest.h"
#include "mergeable_heaps/exceptions.h"
#include "simple_key.h"

enum Func {
    AddHeap, Insert, GetMinimum, ExtractMinimum, Merge
};

// One action that happens to the vector of heaps
// Consists of Func calls with randomized arguments.

class TestAction {
public:
    constexpr static const int func_count_ = 5;
    Func call_;
    SimpleKey key_;
    int index_[2];

    TestAction() = default;

    TestAction(size_t heaps_cnt) {
        static std::mt19937 gen;
        key_.value_ = gen();
        if (heaps_cnt == 0) {
            call_ = Func::AddHeap;
            index_[0] = index_[1] = -1;
        } else {
            call_ = Func(static_cast<size_t>(gen()) % func_count_);
            for (int &i: index_) {
                i = static_cast<size_t>(gen()) % heaps_cnt;
            }
        }
    }
};

// Function that performs the action on the candidate heap array
// and on the correct (stl) heaps and performs all the
// necessary checks.

template<class T, class H>
void RunAction(std::vector<T> &candidate_heaps,
                std::vector<H> &correct_heaps,
                std::vector<size_t> &sizes,
                TestAction action) {

    switch (action.call_) {
        case Func::GetMinimum: {
            SimpleKey candidate_answer{};
            SimpleKey correct_answer{};
            if (sizes[action.index_[0]] > 0) {
                ASSERT_NO_THROW(candidate_answer = candidate_heaps[action.index_[0]].GetMinimum());
                ASSERT_NO_THROW(correct_answer = correct_heaps[action.index_[0]].GetMinimum());
                ASSERT_EQ(candidate_answer, correct_answer);
            } else {
                ASSERT_THROW(candidate_answer = candidate_heaps[action.index_[0]].GetMinimum(), heaps::EmptyHeapException);
                ASSERT_THROW(correct_answer = correct_heaps[action.index_[0]].GetMinimum(), heaps::EmptyHeapException);
            }
            break;
        }
        case Func::AddHeap: {
            ASSERT_NO_THROW(candidate_heaps.emplace_back(action.key_));
            ASSERT_NO_THROW(correct_heaps.emplace_back(action.key_));
            sizes.emplace_back(1);
            break;
        }
        case Func::ExtractMinimum: {
            if (sizes[action.index_[0]] > 0) {
                ASSERT_NO_THROW(candidate_heaps[action.index_[0]].ExtractMinimum());
                ASSERT_NO_THROW(correct_heaps[action.index_[0]].ExtractMinimum());
                --sizes[action.index_[0]];
            } else {
                ASSERT_THROW(candidate_heaps[action.index_[0]].ExtractMinimum(), heaps::EmptyHeapException);
                ASSERT_THROW(correct_heaps[action.index_[0]].ExtractMinimum(), heaps::EmptyHeapException);
            }
            break;
        }
        case Func::Insert: {
            ASSERT_NO_THROW(candidate_heaps[action.index_[0]].Insert(action.key_));
            ASSERT_NO_THROW(correct_heaps[action.index_[0]].Insert(action.key_));
            ++sizes[action.index_[0]];
            break;
        }
        case Func::Merge: {
            if (action.index_[0] != action.index_[1]) {
                ASSERT_NO_THROW(candidate_heaps[action.index_[0]].Merge(candidate_heaps[action.index_[1]]));
                ASSERT_NO_THROW(correct_heaps[action.index_[0]].Merge(correct_heaps[action.index_[1]]));
                sizes[action.index_[0]] += sizes[action.index_[1]];
                sizes[action.index_[1]] = 0;
            } else {
                ASSERT_THROW(candidate_heaps[action.index_[0]].Merge(candidate_heaps[action.index_[1]]), heaps::SelfHeapMergeException);
                ASSERT_THROW(correct_heaps[action.index_[0]].Merge(correct_heaps[action.index_[1]]), heaps::SelfHeapMergeException);
            }
            break;
        }
    }
}

#endif // MERGEABLE_HEAPS_TEST_ACTION_H
