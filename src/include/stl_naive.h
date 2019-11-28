#ifndef MERGEABLEHEAPS_STL_NAIVE_H
#define MERGEABLEHEAPS_STL_NAIVE_H

#include "iheap.h"
#include "exceptions.h"

namespace heaps {

    template<class T>
    class StlHeap : public IHeap<T> {
    public:
        explicit StlHeap(int key);

        std::set<T> elements_;

        void Insert(T x) override;

        T GetMinimum() override;

        void ExtractMinimum() override;

        void Merge(IHeap <T> &x) override;

        void Initialise(int key) override;

        size_t Size() override;
    };

    template<class T>
    void StlHeap<T>::Insert(T x) {
        elements_.insert(x);
    }

    template<class T>
    T StlHeap<T>::GetMinimum() {
        if (elements_.empty()) {
            throw EmptyHeapException();
        }
        return *elements_.begin();
    }

    template<class T>
    void StlHeap<T>::ExtractMinimum() {
        if (elements_.empty()) {
            throw EmptyHeapException();
        }
        elements_.erase(elements_.begin());
    }

    template<class T>
    void StlHeap<T>::Merge(IHeap <T> &x) {
        if (&x == this) {
            return;
        }
        try {
            auto x_casted = dynamic_cast<StlHeap<T> &>(x);
            elements_.insert(x_casted.elements_.begin(), x_casted.elements_.end());
            x_casted.elements_.clear();
        } catch (const std::bad_cast &e) {
            throw WrongHeapTypeException();
        }
    }

    template<class T>
    void StlHeap<T>::Initialise(int key) {
        elements_.insert(key);
    }

    template<class T>
    StlHeap<T>::StlHeap(int key) {
        Initialise(key);
    }

    template<class T>
    size_t StlHeap<T>::Size() {
        return elements_.size();
    }
}

#endif //MERGEABLEHEAPS_STL_NAIVE_H
