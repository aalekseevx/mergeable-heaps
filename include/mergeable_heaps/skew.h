#ifndef MERGEABLE_HEAPS_SKEW_H
#define MERGEABLE_HEAPS_SKEW_H

#include "iheap.h"
#include "exceptions.h"
#include "nodes/skew_heap_node.h"
#include "classical_heap.h"

namespace heaps {
    template<class Key = int>
    class SkewHeap : public ClassicalHeap<Key, SkewHeapNode<Key>> {
    public:
        using ClassicalHeap<Key, SkewHeapNode<Key>>::ClassicalHeap;
    };
}

#endif //MERGEABLE_HEAPS_SKEW_H
