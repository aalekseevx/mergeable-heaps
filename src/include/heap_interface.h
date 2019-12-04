#ifndef MERGEABLE_HEAPS_HEAP_INTERFACE_H
#define MERGEABLE_HEAPS_HEAP_INTERFACE_H

namespace heaps {
    template<class Key>
    class HeapInterface {
    public:
        virtual void Insert(Key x) = 0;

        virtual Key GetMinimum() = 0;

        virtual void ExtractMinimum() = 0;

        virtual void Merge(HeapInterface &x) = 0;

        virtual size_t Size() = 0;

        virtual bool Empty() = 0;

        virtual void Detach() = 0;
    };
} // namespace heaps

#endif // MERGEABLE_HEAPS_HEAP_INTERFACE_H
