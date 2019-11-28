#ifndef MERGEABLEHEAPS_STL_NAIVE_H
#define MERGEABLEHEAPS_STL_NAIVE_H

#include "iheap.h"
#include "exceptions.h"

namespace heaps {

    template <class T>
    class StlHeap : public IHeap<T> {
    public:
        std::set<T> elements_;
        void Insert(T x) override;
        int GetMinimum() override;
        void ExtractMinimum() override;
        void Merge(IHeap<T>& x) override;
    };

    template<class T>
    void StlHeap<T>::Insert(T x) {
        elements_.insert(x);
    }

    template<class T>
    int StlHeap<T>::GetMinimum() {
        return *elements_.begin();
    }

    template<class T>
    void StlHeap<T>::ExtractMinimum() {
        elements_.erase(elements_.begin());
    }

    template<class T>
    void StlHeap<T>::Merge(IHeap<T>& x) {
        try {
            auto x_casted = dynamic_cast<StlHeap<T>&>(x);
            elements_.insert(x_casted.elements_.begin(), x_casted.elements_.end());
            x.clear();
        } catch(const std::bad_cast& e)
        {
            throw WrongHeapTypeException();
        }
    }
}

#endif //MERGEABLEHEAPS_STL_NAIVE_H
