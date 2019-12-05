#ifndef MERGEABLE_HEAPS_SKEW_H
#define MERGEABLE_HEAPS_SKEW_H

#include "heap_interface.h"
#include "exceptions.h"
#include "nodes/skew_heap_node.h"
#include "classical_heap.h"

namespace heaps {
    // Skew Heap implementation. Key is the type of data stored
    template<class Key = int>
    class SkewHeap : public ClassicalHeap<Key, SkewHeapNode<Key>> {
        using Base = ClassicalHeap<Key, SkewHeapNode<Key>>;
    public:
        // Constructor for one-item heap
        explicit SkewHeap(Key key);
    };

    template<class Key>
    SkewHeap<Key>::SkewHeap(Key key) {
        Base::size_ = 1;
        Base::root_ = new heaps::SkewHeapNode<Key>(key, nullptr, nullptr);
    }
} // namespace heaps

#endif // MERGEABLE_HEAPS_SKEW_H
