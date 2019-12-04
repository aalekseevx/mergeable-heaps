#ifndef MERGEABLE_HEAPS_CLASSICAL_HEAP_H
#define MERGEABLE_HEAPS_CLASSICAL_HEAP_H

#include "mergeable_heaps/exceptions.h"
#include "heap_interface.h"
#include "nodes/classical_heap_node.h"

namespace heaps {
    template<class Key, class NodeType>
    class ClassicalHeap : public HeapInterface<Key> {
    protected:
        NodeType *root_;
        
        size_t size_;

        void Merge_(ClassicalHeap &x);

    public:
        ClassicalHeap();

        explicit ClassicalHeap(Key x);

        void Insert(Key x) override;

        Key GetMinimum() override;

        void ExtractMinimum() override;

        void Merge(HeapInterface<Key> &x) override;

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
            return root_->key_;
        }
    }

    template<class Key, class NodeType>
    void ClassicalHeap<Key, NodeType>::ExtractMinimum() {
        if (Empty()) {
            throw EmptyHeapException();
        } else {
            NodeType *left = root_->child_left_;
            NodeType *right = root_->child_right_;
            root_->Detach();
            delete root_;
            root_ = NodeType::Merge_(left, right);
        }
    }

    template<class Key, class NodeType>
    void ClassicalHeap<Key, NodeType>::Merge(HeapInterface<Key> &x) {
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
    size_t ClassicalHeap<Key, NodeType>::Size() {
        return Empty() ? 0 : size_;
    }

    template<class Key, class NodeType>
    bool ClassicalHeap<Key, NodeType>::Empty() {
        return root_ == nullptr;
    }

    template<class Key, class NodeType>
    void ClassicalHeap<Key, NodeType>::Merge_(ClassicalHeap &x) {
        root_ = NodeType::Merge_(root_, x.root_);
    }

    template<class Key, class NodeType>
    ClassicalHeap<Key, NodeType>::ClassicalHeap() : root_(nullptr), size_(0) {}

    template<class Key, class NodeType>
    void ClassicalHeap<Key, NodeType>::Detach() {
        root_ = nullptr;
        size_ = 0;
    }

    // Destructor
    template<class Key, class NodeType>
    ClassicalHeap<Key, NodeType>::~ClassicalHeap<Key, NodeType>() {
        if (root_ != nullptr) {
            delete root_;
        }
    }

    // Copy constructor
    template<class Key, class NodeType>
    ClassicalHeap<Key, NodeType>::ClassicalHeap(const ClassicalHeap<Key, NodeType> &other) : size_(other.size_),
                                                                                             root_(new ClassicalHeapNode<Key, NodeType>(*other.root_)) {}

    // Move constructor
    template<class Key, class NodeType>
    ClassicalHeap<Key, NodeType>::ClassicalHeap(ClassicalHeap<Key, NodeType> &&other) noexcept {
        root_ = nullptr;
        size_ = 0;
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
            root_ = nullptr;
            size_ = 0;
            Swap(other);
        }
        return *this;
    }

    template<class Key, class NodeType>
    void ClassicalHeap<Key, NodeType>::Swap(ClassicalHeap<Key, NodeType> &x) noexcept {
        std::swap(root_, x.root_);
        std::swap(size_, x.size_);
    }

    template<class Key, class NodeType>
    ClassicalHeap<Key, NodeType>::ClassicalHeap(Key x) {
        root_ = new NodeType();
        size_ = 1;
        root_->key_ = x;
    }
} // namespace heaps

#endif // MERGEABLE_HEAPS_CLASSICAL_HEAP_H
