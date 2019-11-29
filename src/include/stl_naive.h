#ifndef MERGEABLEHEAPS_STL_NAIVE_H
#define MERGEABLEHEAPS_STL_NAIVE_H

#include "iheap.h"
#include "exceptions.h"

namespace heaps {

    template<class T>
    class StlHeap : public IHeap<T> {
    private:
        std::set<T> elements_;
        void Merge_(StlHeap <T> &x);
    public:
        explicit StlHeap(int key);

        void Insert(T x) override;

        T GetMinimum() override;

        void ExtractMinimum() override;

        void Merge(IHeap <T> &x) override;

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
            Merge_(dynamic_cast<StlHeap<T> &>(x));
        } catch (const std::bad_cast &e) {
            throw WrongHeapTypeException();
        }
    }

    template<class T>
    StlHeap<T>::StlHeap(int key) {
        elements_.insert(key);
    }

    template<class T>
    size_t StlHeap<T>::Size() {
        return elements_.size();
    }

    template<class T>
    void StlHeap<T>::Merge_(StlHeap<T> &x) {
        elements_.insert(x.elements_.begin(), x.elements_.end());
        x.elements_.clear();
    }
}

#endif //MERGEABLEHEAPS_STL_NAIVE_H
