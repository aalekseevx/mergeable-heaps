#ifndef MERGEABLE_HEAPS_NAIVE_HEAP_H
#define MERGEABLE_HEAPS_NAIVE_HEAP_H

#include "heap_interface.h"
#include "mergeable_heaps/exceptions.h"

namespace heaps {

    // Implementation of heaps interface using std::multiset.
    template<class Key>
    class StlHeap : public HeapInterface<Key> {
    private:
        std::multiset<Key> elements_;
        void Merge_(StlHeap <Key> &x);
    public:
        explicit StlHeap(Key key);

        void Insert(Key x) override;

        Key GetMinimum() override;

        void ExtractMinimum() override;

        void Merge(HeapInterface <Key> &x) override;

        size_t Size() override;

        bool Empty() override;

        void Detach() override;

        std::vector<Key> Data();
    };

    template<class Key>
    void StlHeap<Key>::Insert(Key x) {
        elements_.insert(x);
    }

    template<class Key>
    Key StlHeap<Key>::GetMinimum() {
        if (Empty()) {
            throw EmptyHeapException();
        }
        return *elements_.begin();
    }

    template<class Key>
    void StlHeap<Key>::ExtractMinimum() {
        if (elements_.empty()) {
            throw EmptyHeapException();
        }
        elements_.erase(elements_.begin());
    }

    template<class Key>
    void StlHeap<Key>::Merge(HeapInterface <Key> &x) {
        if (&x == this) {
            throw SelfHeapMergeException();
        }
        try {
            Merge_(dynamic_cast<StlHeap<Key> &>(x));
        } catch (const std::bad_cast &e) {
            throw WrongHeapTypeException();
        }
    }

    template<class Key>
    StlHeap<Key>::StlHeap(Key key) {
        elements_.insert(key);
    }

    template<class Key>
    size_t StlHeap<Key>::Size() {
        return elements_.size();
    }

    template<class Key>
    void StlHeap<Key>::Merge_(StlHeap<Key> &x) {
        elements_.insert(x.elements_.begin(), x.elements_.end());
        x.elements_.clear();
    }

    template<class Key>
    bool StlHeap<Key>::Empty() {
        return Size() == 0;
    }

    template<class Key>
    void StlHeap<Key>::Detach() {

    }

    template<class Key>
    std::vector<Key> StlHeap<Key>::Data() {
        return std::vector<Key>(elements_.begin(), elements_.end());
    }
}

#endif // MERGEABLE_HEAPS_NAIVE_HEAP_H
