#ifndef MERGEABLE_HEAPS_CLASSICAL_HEAP_H
#define MERGEABLE_HEAPS_CLASSICAL_HEAP_H

#include "mergeable_heaps/exceptions.h"
#include "heap_interface.h"
#include "nodes/classical_heap_node.h"

namespace heaps {
    // Classical Heap implementation. Key is the type of data stored
    // Leftist and Skew Heaps are based in the ClassicalHeap
    template<class Key, class NodeType>
    class ClassicalHeap :public HeapInterface<Key> {
    protected:
        // Link to the root of the tree with the minimal degree.
        // If there is none, nullptr.
        NodeType *root_;
        // Number of items in the heap
        size_t size_;

        // Methods merges heap "x" to *this heap.
        // heap "x" becomes empty.
        void Merge_(ClassicalHeap &x);

    public:
        // Constructor of the empty heap
        ClassicalHeap();

        // Constructor of the one-item heap
        explicit ClassicalHeap(Key x);

        // Inserts an item into the heap
        void Insert(Key x) override;

        // Return the minimal item in heap.
        // Throws EmptyHeapException, if there is none
        Key GetMinimum() override;

        // Extracts minimal item from the heap.
        // Throws EmptyHeapException, if there is none
        void ExtractMinimum() override;

        // Merges an abstract heap into *this.
        // Throws WrongHeapTypeException, if x is not a BinomialHeap
        void Merge(HeapInterface<Key> &x) override;

        // Return number of items in the heap
        size_t Size() override;

        // Checks if the heap is empty
        bool Empty() override;

        // Detaches heap from its nodes without deleting them
        // Now, it's user's responsibility to free node's memory.
        void Detach() override;

        //
        // Rule of Five functions
        //

        // Destructor. Destructs the heap with all it's nodes
        // Unless they are detached.
        ~ClassicalHeap<Key, NodeType>();

        // Copy constructor. Creates the copy of the heap and all it's nodes
        ClassicalHeap<Key, NodeType>(const ClassicalHeap<Key, NodeType> &other);

        // Move constructor. Creates the copy of the heap by stealing resources.
        // Other heap is left as newly initialized.
        ClassicalHeap<Key, NodeType>(ClassicalHeap<Key, NodeType> &&other) noexcept;

        // Copy assignment operator
        ClassicalHeap<Key, NodeType> &operator=(const ClassicalHeap<Key, NodeType> &other);

        // Move assignment operator
        ClassicalHeap<Key, NodeType> &operator=(ClassicalHeap<Key, NodeType> &&other) noexcept;

        // Swap function for "Copy and Swap" idiom
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
