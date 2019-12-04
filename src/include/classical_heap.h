#ifndef MERGEABLE_HEAPS_CLASSICAL_HEAP_H
#define MERGEABLE_HEAPS_CLASSICAL_HEAP_H

#include "mergeable_heaps/exceptions.h"
#include "iheap.h"
#include "nodes/classical_heap_node.h"

namespace heaps {
    template<class Key, class NodeType>
    class ClassicalHeap : public IHeap<Key> {
    private:
        NodeType *root;
        
        size_t size;

        void Merge_(ClassicalHeap &x);

    public:
        ClassicalHeap();

        explicit ClassicalHeap(Key key);

        void Insert(Key x) override;

        Key GetMinimum() override;

        void ExtractMinimum() override;

        void Merge(IHeap<Key> &x) override;

        size_t Size() override;

        bool Empty() override;

        void Detach() override;

        //
        // Rule of Five functions
        //
        
        ~ClassicalHeap<Key, NodeType>();

        ClassicalHeap<Key, NodeType>(const ClassicalHeap<Key, NodeType> &other);

        ClassicalHeap<Key, NodeType>(ClassicalHeap<Key, NodeType> &&other) noexcept;

        ClassicalHeap<Key, NodeType> &operator=(const ClassicalHeap<Key, NodeType> &other);

        ClassicalHeap<Key, NodeType> &operator=(ClassicalHeap<Key, NodeType> &&other) noexcept;

        void Swap(ClassicalHeap<Key, NodeType> &x) noexcept;
    };

    template<class Key, class NodeType>
    void ClassicalHeap<Key, NodeType>::Insert(Key x) {
        Merge(*new ClassicalHeap(x));
    }

    template<class Key, class NodeType>
    Key ClassicalHeap<Key, NodeType>::GetMinimum() {
        if (Empty()) {
            throw EmptyHeapException();
        } else {
            return root->key;
        }
    }

    template<class Key, class NodeType>
    void ClassicalHeap<Key, NodeType>::ExtractMinimum() {
        if (Empty()) {
            throw EmptyHeapException();
        } else {
            NodeType *left = root->child_left;
            NodeType *right = root->child_right;
            root->Detach();
            delete root;
            root = NodeType::Merge_(left, right);
        }
    }

    template<class Key, class NodeType>
    void ClassicalHeap<Key, NodeType>::Merge(IHeap<Key> &x) {
        if (&x == this) {
            throw SelfHeapMergeException();
        }
        try {
            Merge_(dynamic_cast<ClassicalHeap<Key, NodeType> &>(x));
            x.Detach();
        } catch (const std::bad_cast &e) {
            throw WrongHeapTypeException();
        }
    }

    template<class Key, class NodeType>
    ClassicalHeap<Key, NodeType>::ClassicalHeap(Key key) : size(1) {
        root = new NodeType(key, nullptr, nullptr);
    }

    template<class Key, class NodeType>
    size_t ClassicalHeap<Key, NodeType>::Size() {
        return Empty() ? 0 : size;
    }

    template<class Key, class NodeType>
    bool ClassicalHeap<Key, NodeType>::Empty() {
        return root == nullptr;
    }

    template<class Key, class NodeType>
    void ClassicalHeap<Key, NodeType>::Merge_(ClassicalHeap &x) {
        root = NodeType::Merge_(root, x.root);
    }

    template<class Key, class NodeType>
    ClassicalHeap<Key, NodeType>::ClassicalHeap() : root(nullptr), size(0) {}

    template<class Key, class NodeType>
    void ClassicalHeap<Key, NodeType>::Detach() {
        root = nullptr;
        size = 0;
    }

    // Destructor
    template<class Key, class NodeType>
    ClassicalHeap<Key, NodeType>::~ClassicalHeap<Key, NodeType>() {
        if (root != nullptr) {
            delete root;
        }
    }

    // Copy constructor
    template<class Key, class NodeType>
    ClassicalHeap<Key, NodeType>::ClassicalHeap(const ClassicalHeap<Key, NodeType> &other) : size(other.size),
                                                                         root(new ClassicalHeapNode(*other.root)) {}

    // Move constructor
    template<class Key, class NodeType>
    ClassicalHeap<Key, NodeType>::ClassicalHeap(ClassicalHeap<Key, NodeType> &&other) noexcept {
        root = nullptr;
        size = 0;
        Swap(other);
    }

    // Copy assignment operator
    template<class Key, class NodeType>
    ClassicalHeap<Key, NodeType> &ClassicalHeap<Key, NodeType>::operator=(const ClassicalHeap<Key, NodeType> &other) {
        if (this != &other) {
            ClassicalHeap tmp(other);
            Swap(tmp);
        }
        return *this;
    }

    // Move assignment operator
    template<class Key, class NodeType>
    ClassicalHeap<Key, NodeType> &ClassicalHeap<Key, NodeType>::operator=(ClassicalHeap<Key, NodeType> &&other) noexcept {
        if (this != &other) {
            root = nullptr;
            size = 0;
            Swap(other);
        }
        return *this;
    }

    template<class Key, class NodeType>
    void ClassicalHeap<Key, NodeType>::Swap(ClassicalHeap<Key, NodeType> &x) noexcept {
        std::swap(root, x.root);
        std::swap(size, x.size);
    }
}

#endif //MERGEABLE_HEAPS_CLASSICAL_HEAP_H
