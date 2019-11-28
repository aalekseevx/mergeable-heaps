#ifndef MERGEABLEHEAPS_BINOMIAL_H
#define MERGEABLEHEAPS_BINOMIAL_H

#include "iheap.h"
#include "exceptions.h"

namespace heaps {
    template <class T>
    class BinomialHeap : public IHeap<T> {
    public:
        explicit BinomialHeap (int key);
        void Insert(T x) override;
        int GetMinimum() override;
        void ExtractMinimum() override;
        void Merge(IHeap<T>& x) override;
        void Initialise(int key) override;
        size_t Size() override;
    };

    template<class T>
    void BinomialHeap<T>::Insert(T x) {
    }

    template<class T>
    int BinomialHeap<T>::GetMinimum() {
    }

    template<class T>
    void BinomialHeap<T>::ExtractMinimum() {
    }

    template<class T>
    void BinomialHeap<T>::Merge(IHeap<T>& x) {
        try {
            auto x_casted = dynamic_cast<BinomialHeap<T> &>(x);
        } catch(const std::bad_cast& e)
        {
            throw WrongHeapTypeException();
        }
    }

    template<class T>
    void BinomialHeap<T>::Initialise(int key) {

    }

    template<class T>
    BinomialHeap<T>::BinomialHeap(int key) {

    }

    template<class T>
    size_t BinomialHeap<T>::Size() {

    }
}

#endif //MERGEABLEHEAPS_BINOMIAL_H
