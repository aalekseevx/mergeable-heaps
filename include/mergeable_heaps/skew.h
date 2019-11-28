#ifndef MERGEABLEHEAPS_SKEW_H
#define MERGEABLEHEAPS_SKEW_H

#include "iheap.h"

namespace heaps {
    template <class T>
    class SkewHeap : public IHeap<T> {
    public:
        void Insert(T x) override;
        int GetMinimum() override;
        void ExtractMinimum() override;
        void Merge(IHeap<T>& x) override;
    };

    template<class T>
    void SkewHeap<T>::Insert(T x) {
    }

    template<class T>
    int SkewHeap<T>::GetMinimum() {
    }

    template<class T>
    void SkewHeap<T>::ExtractMinimum() {
    }

    template<class T>
    void SkewHeap<T>::Merge(IHeap<T>& x) {
        try {
            auto x_casted = dynamic_cast<SkewHeap<T> &>(x);
        } catch(const std::bad_cast& e)
        {
            throw WrongHeapTypeException();
        }
    }
}

#endif //MERGEABLEHEAPS_SKEW_H
