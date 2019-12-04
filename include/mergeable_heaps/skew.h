#ifndef MERGEABLE_HEAPS_SKEW_H
#define MERGEABLE_HEAPS_SKEW_H

#include "iheap.h"
#include "exceptions.h"
#include "nodes/skew_heap_node.h"
#include "classical_heap.h"

namespace heaps {
    template<class Key = int>
    class SkewHeap : public ClassicalHeap<Key, SkewHeapNode<Key>> {
        using Base = ClassicalHeap<Key, SkewHeapNode<Key>>;
    public:
        explicit SkewHeap(Key key);
    };

    template<class Key>
    SkewHeap<Key>::SkewHeap(Key key) {
        Base::size = 1;
        Base::root = new heaps::SkewHeapNode<Key>(key, nullptr, nullptr);
    }
}

#endif //MERGEABLE_HEAPS_SKEW_H
