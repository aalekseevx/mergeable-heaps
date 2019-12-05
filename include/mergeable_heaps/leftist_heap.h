#ifndef MERGEABLE_HEAPS_LEFTIST_H
#define MERGEABLE_HEAPS_LEFTIST_H

#include "classical_heap.h"
#include "nodes/leftist_heap_node.h"

namespace heaps {
    // Leftist Heap implementation. Key is the type of data stored
    template<class Key=int>
    class LeftistHeap : public ClassicalHeap<Key, LeftistHeapNode<Key>> {
        using Base = ClassicalHeap<Key, LeftistHeapNode<Key>>;
    public:

        explicit LeftistHeap(Key key);
    };

    template<class Key>
    LeftistHeap<Key>::LeftistHeap(Key key) {
        Base::size_ = 1;
        Base::root_ = new LeftistHeapNode<Key>(key, nullptr, nullptr, 0);
    }
} // namespace heaps

#endif // MERGEABLE_HEAPS_LEFTIST_H