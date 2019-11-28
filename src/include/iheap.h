#ifndef MERGEABLEHEAPS_IHEAP_H
#define MERGEABLEHEAPS_IHEAP_H

namespace heaps {
    template<class T>
    class IHeap {
        virtual void Initialise(int key) = 0;

        virtual void Insert(T x) = 0;

        virtual T GetMinimum() = 0;

        virtual void ExtractMinimum() = 0;

        virtual void Merge(IHeap &x) = 0;

        virtual size_t Size() = 0;
    };
}

#endif //MERGEABLEHEAPS_IHEAP_H
