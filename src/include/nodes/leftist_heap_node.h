#ifndef MERGEABLE_HEAPS_LEFTIST_HEAP_NODE_H
#define MERGEABLE_HEAPS_LEFTIST_HEAP_NODE_H

#include "classical_heap_node.h"

namespace heaps {

    template<class Key>
    class LeftistHeapNode : public ClassicalHeapNode<Key, LeftistHeapNode<Key>> {
    public:
        size_t rank_;
        using Base = ClassicalHeapNode<Key, LeftistHeapNode<Key>>;

        LeftistHeapNode();

        LeftistHeapNode(Key key, LeftistHeapNode<Key> *child_left, LeftistHeapNode<Key> *child_right, size_t rank);

        void UpdateRank();

        static LeftistHeapNode *Merge_(LeftistHeapNode *root_1, LeftistHeapNode *root_2);
    };

    template<class Key>
    LeftistHeapNode<Key>::LeftistHeapNode(Key key, LeftistHeapNode<Key> *child_left, LeftistHeapNode<Key> *child_right,
                                          size_t rank) : Base(key, child_left, child_right), rank_(rank) {}

    template<class Key>
    void LeftistHeapNode<Key>::UpdateRank() {
        rank_ = 1 + std::min(
                (Base::child_left_ == nullptr ? 0 : Base::child_left_->rank_),
                (Base::child_right_ == nullptr ? 0 : Base::child_right_->rank_)
        );
    }

    template<class Key>
    LeftistHeapNode<Key> *LeftistHeapNode<Key>::Merge_(LeftistHeapNode *root_1, LeftistHeapNode *root_2) {
        if (root_1 == nullptr || root_2 == nullptr) {
            return root_1 == nullptr ? root_2 : root_1;
        }
        if (!(root_1->key_ < root_2->key_)) {
            std::swap(root_1, root_2);
        }

        root_1->child_right_ = Merge_(root_1->child_right_, root_2);

        if (root_1->child_left_ == nullptr || root_1->child_left_->rank_ < root_1->child_right_->rank_) {
            std::swap(root_1->child_left_, root_1->child_right_);
        }
        root_1->UpdateRank();

        return root_1;
    }

    template<class Key>
    LeftistHeapNode<Key>::LeftistHeapNode() : Base(), rank_(0) {}
} // namespace heaps

#endif // MERGEABLE_HEAPS_LEFTIST_HEAP_NODE_H
