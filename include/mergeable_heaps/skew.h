#ifndef MERGEABLEHEAPS_SKEW_H
#define MERGEABLEHEAPS_SKEW_H

#include "iheap.h"
#include "exceptions.h"
#include "nodes/skew_heap_node.h"

namespace heaps {
    template<class Key = int>
    class SkewHeap : public IHeap<Key> {
        SkewHeapNode<Key> *root;
        size_t size;

        void Merge_(SkewHeap &x);

    public:
        SkewHeap();

        explicit SkewHeap(Key key);

        void Insert(Key x) override;

        Key GetMinimum() override;

        void ExtractMinimum() override;

        void Merge(IHeap <Key> &x) override;

        size_t Size() override;

        bool Empty() override;

        void Detach() override;

        // Rule of Five functions
        ~SkewHeap<Key>();

        SkewHeap<Key>(const SkewHeap<Key> &other);

        SkewHeap<Key>(SkewHeap<Key> &&other) noexcept;

        SkewHeap<Key> &operator=(const SkewHeap<Key> &other);

        SkewHeap<Key> &operator=(SkewHeap<Key> &&other) noexcept;

        void Swap(SkewHeap<Key> &x) noexcept;
    };

    template<class Key>
    void SkewHeap<Key>::Insert(Key x) {
        Merge(*new SkewHeap(x));
    }

    template<class Key>
    Key SkewHeap<Key>::GetMinimum() {
        if (Empty()) {
            throw EmptyHeapException();
        } else {
            return root->key;
        }
    }

    template<class Key>
    void SkewHeap<Key>::ExtractMinimum() {
        if (Empty()) {
            throw EmptyHeapException();
        } else {
            SkewHeapNode<Key> *left = root->child_left;
            SkewHeapNode<Key> *right = root->child_right;
            root->Detach();
            delete root;
            root = SkewHeapNode<Key>::Merge_(left, right);
        }
    }

    template<class Key>
    void SkewHeap<Key>::Merge(IHeap <Key> &x) {
        if (&x == this) {
            throw SelfHeapMergeException();
        }
        try {
            Merge_(dynamic_cast<SkewHeap<Key> &>(x));
            x.Detach();
        } catch (const std::bad_cast &e) {
            throw WrongHeapTypeException();
        }
    }

    template<class Key>
    SkewHeap<Key>::SkewHeap(Key key) : size(1) {
        root = new SkewHeapNode<Key>(key, nullptr, nullptr);
    }

    template<class Key>
    size_t SkewHeap<Key>::Size() {
        return Empty() ? 0 : size;
    }

    template<class Key>
    bool SkewHeap<Key>::Empty() {
        return root == nullptr;
    }

    template<class Key>
    void SkewHeap<Key>::Merge_(SkewHeap &x) {
        root = SkewHeapNode<Key>::Merge_(root, x.root);
    }

    template<class Key>
    SkewHeap<Key>::SkewHeap() : root(nullptr), size(0) {}

    template<class Key>
    void SkewHeap<Key>::Detach() {
        root = nullptr;
        size = 0;
    }

    // Destructor
    template<class Key>
    SkewHeap<Key>::~SkewHeap<Key>() {
        if (root != nullptr) {
            delete root;
        }
    }

    // Copy constructor
    template<class Key>
    SkewHeap<Key>::SkewHeap(const SkewHeap<Key> &other) : size(other.size), root(new SkewHeapNode(*other.root)) {}

    // Move constructor
    template<class Key>
    SkewHeap<Key>::SkewHeap(SkewHeap<Key> &&other) noexcept {
        root = nullptr;
        size = 0;
        Swap(other);
    }

    // Copy assignment operator
    template<class Key>
    SkewHeap<Key> &SkewHeap<Key>::operator=(const SkewHeap<Key> &other) {
        if (this != &other) {
            SkewHeap tmp(other);
            Swap(tmp);
        }
        return *this;
    }

    // Move assignment operator
    template<class Key>
    SkewHeap<Key> &SkewHeap<Key>::operator=(SkewHeap<Key> &&other) noexcept {
        if (this != &other) {
            root = nullptr;
            size = 0;
            Swap(other);
        }
        return *this;
    }

    template<class Key>
    void SkewHeap<Key>::Swap(SkewHeap<Key> &x) noexcept {
        std::swap(root, x.root);
        std::swap(size, x.size);
    }
}

#endif //MERGEABLEHEAPS_SKEW_H
