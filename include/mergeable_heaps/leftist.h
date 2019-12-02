#ifndef MERGEABLEHEAPS_LEFTIST_H
#define MERGEABLEHEAPS_LEFTIST_H

#include "iheap.h"

namespace heaps {
    template<class T>
    class LeftistHeap : public IHeap<T> {
    public:
        explicit LeftistHeap(int key);

        void Insert(T x) override;

        T GetMinimum() override;

        void ExtractMinimum() override;

        void Merge(IHeap <T> &x) override;

        void Initialise(int key) override;

        size_t Size() override;

        bool Empty() override;
    };

    template<class T>
    void LeftistHeap<T>::Insert(T x) {
    }

    template<class T>
    T LeftistHeap<T>::GetMinimum() {
    }

    template<class T>
    void LeftistHeap<T>::ExtractMinimum() {
    }

    template<class T>
    void LeftistHeap<T>::Merge(IHeap <T> &x) {
        if (&x == this) {
            throw SelfHeapMerge();
        }
        try {
            auto x_casted = dynamic_cast<LeftistHeap<T> &>(x);
        } catch (const std::bad_cast &e) {
            throw WrongHeapTypeException();
        }
    }

    template<class T>
    void LeftistHeap<T>::Initialise(int key) {

    }

    template<class T>
    LeftistHeap<T>::LeftistHeap(int key) {

    }

    template<class T>
    size_t LeftistHeap<T>::Size() {

    }

    template<class T>
    bool LeftistHeap<T>::Empty() {

    }
}

#endif //MERGEABLEHEAPS_LEFTIST_H
