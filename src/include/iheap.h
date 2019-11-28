#ifndef MERGEABLEHEAPS_IHEAP_H
#define MERGEABLEHEAPS_IHEAP_H

namespace heaps {
    template <class T>
    class IHeap {
        virtual void Insert(T x) = 0;
        virtual int GetMinimum() = 0;
        virtual void ExtractMinimum() = 0;
        virtual void Merge(IHeap& x) = 0;
    };
}

#endif //MERGEABLEHEAPS_IHEAP_H
