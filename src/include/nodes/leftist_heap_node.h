#ifndef MERGEABLE_HEAPS_LEFTIST_HEAP_NODE_H
#define MERGEABLE_HEAPS_LEFTIST_HEAP_NODE_H

#include "classical_heap_node.h"

namespace heaps {

    template<class Key>
    class LeftistHeapNode : public ClassicalHeapNode<Key, LeftistHeapNode<Key>> {
    public:
        size_t rank;
        using Base = ClassicalHeapNode<Key, LeftistHeapNode<Key>>;

        LeftistHeapNode();

        LeftistHeapNode(Key key, LeftistHeapNode<Key> *child_left, LeftistHeapNode<Key> *child_right, size_t rank);

        void UpdateRank();

        static LeftistHeapNode *Merge_(LeftistHeapNode *root_1, LeftistHeapNode *root_2);
    };

    template<class Key>
    LeftistHeapNode<Key>::LeftistHeapNode(Key key, LeftistHeapNode<Key> *child_left, LeftistHeapNode<Key> *child_right,
                                          size_t rank) : Base(key, child_left, child_right), rank(rank) {}

    template<class Key>
    void LeftistHeapNode<Key>::UpdateRank() {
        rank = 1 + std::min(
                (Base::child_left == nullptr ? 0 : Base::child_left->rank),
                (Base::child_right == nullptr ? 0 : Base::child_right->rank)
        );
    }

    template<class Key>
    LeftistHeapNode<Key> *LeftistHeapNode<Key>::Merge_(LeftistHeapNode *root_1, LeftistHeapNode *root_2) {
        if (root_1 == nullptr || root_2 == nullptr) {
            return root_1 == nullptr ? root_2 : root_1;
        }
        if (root_1->key > root_2->key) {
            std::swap(root_1, root_2);
        }

        root_1->child_right = Merge_(root_1->child_right, root_2);

        if (root_1->child_left == nullptr || root_1->child_left->rank < root_1->child_right->rank) {
            std::swap(root_1->child_left, root_1->child_right);
        }
        root_1->UpdateRank();

        return root_1;
    }

    template<class Key>
    LeftistHeapNode<Key>::LeftistHeapNode() : Base(), rank(0) {}
} // namespace heaps

#endif //MERGEABLE_HEAPS_LEFTIST_HEAP_NODE_H
