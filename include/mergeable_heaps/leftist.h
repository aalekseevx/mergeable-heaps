#ifndef MERGEABLEHEAPS_LEFTIST_H
#define MERGEABLEHEAPS_LEFTIST_H

#include "iheap.h"

namespace heaps {
    template <class T>
    class LeftistHeap : public IHeap<T> {
    public:
        void Insert(T x) override;
        int GetMinimum() override;
        void ExtractMinimum() override;
        void Merge(IHeap<T>& x) override;
    };

    template<class T>
    void LeftistHeap<T>::Insert(T x) {
    }

    template<class T>
    int LeftistHeap<T>::GetMinimum() {
    }

    template<class T>
    void LeftistHeap<T>::ExtractMinimum() {
    }

    template<class T>
    void LeftistHeap<T>::Merge(IHeap<T>& x) {
        try {
            auto x_casted = dynamic_cast<LeftistHeap<T> &>(x);
        } catch(const std::bad_cast& e)
        {
            throw WrongHeapTypeException();
        }
    }
}

#endif //MERGEABLEHEAPS_LEFTIST_H
