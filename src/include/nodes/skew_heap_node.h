#ifndef MERGEABLE_HEAPS_SKEW_HEAP_NODE_H
#define MERGEABLE_HEAPS_SKEW_HEAP_NODE_H

#include "classical_heap_node.h"

namespace heaps {
    // One node of the skew heap, specifies ClassicalHeapNode.
    template<class Key>
    class SkewHeapNode : public ClassicalHeapNode<Key, SkewHeapNode<Key>> {
    public:
        // Importing Base's constructors
        using ClassicalHeapNode<Key, SkewHeapNode>::ClassicalHeapNode;

        SkewHeapNode();

        // Merges two subtrees and returns the result. "Steals" resources from root_1, root_2.
        static SkewHeapNode<Key> *Merge_(SkewHeapNode<Key> *root_1, SkewHeapNode<Key> *root_2);
    };

    template<class Key>
    SkewHeapNode<Key> *SkewHeapNode<Key>::Merge_(SkewHeapNode<Key> *root_1, SkewHeapNode<Key> *root_2) {
        if (root_1 == nullptr || root_2 == nullptr) {
            return root_1 == nullptr ? root_2 : root_1;
        }
        if (!(root_1->key_ < root_2->key_)) {
            std::swap(root_1, root_2);
        }
        SkewHeapNode *tmp_root = root_1->child_right_;
        std::swap(root_1->child_left_, root_1->child_right_);
        root_1->child_left_ = SkewHeapNode::Merge_(tmp_root, root_2);
        return root_1;
    }

    template<class Key>
    SkewHeapNode<Key>::SkewHeapNode() = default;
} // namespace heaps

#endif // MERGEABLE_HEAPS_SKEW_HEAP_NODE_H
