#ifndef MERGEABLE_HEAPS_HEAP_INTERFACE_H
#define MERGEABLE_HEAPS_HEAP_INTERFACE_H

namespace heaps {
    // Interface of every mergeable heap
    template<class Key>
    class HeapInterface {
    public:
        // Insert a value into the heap
        virtual void Insert(Key x) = 0;

        // Find the minimal value in the heap
        virtual Key GetMinimum() = 0;

        // Delete the minimal value
        virtual void ExtractMinimum() = 0;

        // Merge heap x to first. Heap x will be
        // as newly initialized
        virtual void Merge(HeapInterface &x) = 0;

        // Returns number of elements in the heap
        virtual size_t Size() = 0;

        // Checks if heap is empty
        virtual bool Empty() = 0;

        // Detaches the heap from its nodes.
        // Nodes are not deleted.
        virtual void Detach() = 0;

        // Virtual destructor
        virtual ~HeapInterface() = 0;
    };

    template <class Key>
    HeapInterface<Key>::~HeapInterface() = default;
} // namespace heaps

#endif // MERGEABLE_HEAPS_HEAP_INTERFACE_H
