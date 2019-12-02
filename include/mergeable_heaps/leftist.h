#ifndef MERGEABLEHEAPS_LEFTIST_H
#define MERGEABLEHEAPS_LEFTIST_H

#include "iheap.h"

namespace heaps {
    template<class Key=int>
    class LeftistHeap : public IHeap<Key> {
    public:
        explicit LeftistHeap(Key key);

        void Insert(Key x) override;

        Key GetMinimum() override;

        void ExtractMinimum() override;

        void Merge(IHeap <Key> &x) override;

        size_t Size() override;
    };

    template<class Key>
    void LeftistHeap<Key>::Insert(Key x) {
    }

    template<class Key>
    Key LeftistHeap<Key>::GetMinimum() {
    }

    template<class Key>
    void LeftistHeap<Key>::ExtractMinimum() {
    }

    template<class Key>
    void LeftistHeap<Key>::Merge(IHeap <Key> &x) {
        if (&x == this) {
            return;
        }
        try {
            Merge_(dynamic_cast<LeftistHeap<Key> &>(x));
        } catch (const std::bad_cast &e) {
            throw WrongHeapTypeException();
        }
    }

    template<class Key>
    LeftistHeap<Key>::LeftistHeap(Key key) {

    }

    template<class Key>
    size_t LeftistHeap<Key>::Size() {

    }
}

#endif //MERGEABLEHEAPS_LEFTIST_H
