#ifndef MERGEABLE_HEAPS_BINOMIAL_H
#define MERGEABLE_HEAPS_BINOMIAL_H

#include <string>
#include <algorithm>
#include "heap_interface.h"
#include "exceptions.h"
#include "nodes/binomial_heap_node.h"

namespace heaps {
    // Binomial Heap implementation. Key is the type of data stored
    template<class Key>
    class BinomialHeap : public HeapInterface<Key> {
    private:
        // Link to the root of the tree with the minimal degree.
        // If there is none, nullptr.
        BinomialHeapNode<Key> *root_;

        // As we save memory and don't store size of the subtree in nodes,
        // some heaps, created by Merge might not contain size information.
        // They will throw a RestrictedMethodException for Size() and Empty() methods.
        bool is_temporary_;
        size_t size_;

        // Method finds the minimal node in the heap and returns pointer.
        // Throws an EmptyHeapException(), if there is none
        BinomialHeapNode<Key> *FindMinimalNode();

        // Method accepts on of the roots of the trees and extracts it from the heap.
        // It is detached and deleted.
        void ExtractTopVertex(BinomialHeapNode<Key> *v);

        // The method cuts the vertex off its children and then destroys it.
        // The node itself is destroyed. The children are organised into the returning heap.
        // Heap has some restricted methods and it marked temporary.
        BinomialHeap<Key> CutVertex(BinomialHeapNode<Key> *v);

        // Methods merges heap "x" to *this heap.
        // heap "x" becomes empty.
        void Merge_(BinomialHeap<Key> &x);

        // Method merges two lists of roots using merge sort
        // It returns the pointer to the head of the list, where
        // roots are in non-descending order.
        BinomialHeapNode<Key> *MergeRootsAsLists(BinomialHeapNode<Key> *v1, BinomialHeapNode<Key> *v2);

        // The method consequently merges trees in lists so that
        // there there every degree is unique. Works in-place
        static void MakeDegreesUnique(BinomialHeapNode<Key> *v);

        // Private constructor from the Node
        // Makes new heap "temporary" and restricts Size(), Empty()
        explicit BinomialHeap(BinomialHeapNode<Key> *root);

        // Detaches heap from its nodes without deleting them
        // Now, it's user's responsibility to free node's memory.
        void Detach() override;

    public:

        // Constructor for one-item heap
        explicit BinomialHeap(Key key);

        // Constructor for empty heap
        explicit BinomialHeap();

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

        // Return size, may be restricted
        size_t Size() override;

        // Return true if heap is empty, false otherwise, may be restricted.
        bool Empty() override;

        // Returns sorted std::vector with all the keys from the heap.
        // Mainly for debug purposes.
        std::vector<Key> Data();

        //
        // Rule of Five functions
        //

        // Destructor. Destructs the heap with all it's nodes
        // Unless they are detached.
        ~BinomialHeap<Key>();

        // Copy constructor. Creates the copy of the heap and all it's nodes
        BinomialHeap<Key>(const BinomialHeap<Key> &other);

        // Move constructor. Creates the copy of the heap by stealing resources.
        // Other heap is left as newly initialized.
        BinomialHeap<Key>(BinomialHeap<Key> &&other) noexcept;

        // Copy assignment operator
        BinomialHeap<Key> &operator=(const BinomialHeap<Key> &other);

        // Move assignment operator
        BinomialHeap<Key> &operator=(BinomialHeap<Key> &&other) noexcept;

        // Swap function for "Copy and Swap" idiom
        void Swap(BinomialHeap<Key> &x) noexcept;
    };

    template<class Key>
    void BinomialHeap<Key>::Insert(Key x) {
        BinomialHeap<Key> tmp(x);
        Merge(tmp);
        // Now tmp is empty and will be destructed.
    }

    template<class Key>
    Key BinomialHeap<Key>::GetMinimum() {
        return FindMinimalNode()->key_;
    }

    template<class Key>
    void BinomialHeap<Key>::ExtractTopVertex(BinomialHeapNode<Key> *v) {
        BinomialHeapNode<Key> *predecessor = nullptr;
        for (BinomialHeapNode<Key> *i = root_; i != v; i = i->sibling_) {
            predecessor = i;
        }
        if (predecessor == nullptr) {
            root_ = v->sibling_;
        } else {
            predecessor->sibling_ = v->sibling_;
        }
        BinomialHeap<Key> tmp(std::move(CutVertex(v)));
        Merge(tmp);
        // Decreasing size and disabling restricting
        size_ -= 1;
        is_temporary_ = false;
    }

    template<class Key>
    void BinomialHeap<Key>::ExtractMinimum() {
        ExtractTopVertex(FindMinimalNode());
    }

    template<class Key>
    void BinomialHeap<Key>::Merge_(BinomialHeap<Key> &x) {
        if (root_ == nullptr || x.root_ == nullptr) {
            root_ = root_ == nullptr ? x.root_ : root_;
            return;
        }
        root_ = MergeRootsAsLists(root_, x.root_);
        MakeDegreesUnique(root_);
        BinomialHeapNode<Key>::Raise(root_);
    }

    template<class Key>
    void BinomialHeap<Key>::Merge(HeapInterface<Key> &x) {
        if (&x == this) {
            throw SelfHeapMergeException();
        }
        try {
            auto &casted = dynamic_cast<BinomialHeap<Key> &>(x);
            Merge_(casted);
            // Trying to update size.
            // If merged heap was temporary, we can't rely on the size field again.
            try {
                size_ += casted.Size();
            } catch (const RestrictedMethodException &e) {
                is_temporary_ = true;
            }
            x.Detach();
        } catch (const std::bad_cast &e) {
            throw WrongHeapTypeException();
        }
    }

    template<class Key>
    BinomialHeap<Key>::BinomialHeap(Key key) : size_(1), is_temporary_(false) {
        root_ = new BinomialHeapNode<Key>(key, nullptr, nullptr, nullptr, 0u);
    }

    template<class Key>
    size_t BinomialHeap<Key>::Size() {
        if (is_temporary_) {
            throw RestrictedMethodException();
        }
        return size_;
    }

    template<class Key>
    BinomialHeapNode<Key> *BinomialHeap<Key>::FindMinimalNode() {
        if (root_ == nullptr) {
            throw EmptyHeapException();
        }
        BinomialHeapNode<Key> *minimal_node = root_;
        for (BinomialHeapNode<Key> *i = root_; i != nullptr; i = i->sibling_) {
            if (i->key_ < minimal_node->key_) {
                minimal_node = i;
            }
        }
        return minimal_node;
    }

    // TODO DetachSibling
    template<class Key>
    BinomialHeap<Key> BinomialHeap<Key>::CutVertex(BinomialHeapNode<Key> *v) {
        BinomialHeapNode<Key> *first = v->child_;
        if (first == nullptr) {
            return BinomialHeap<Key>();
        }
        BinomialHeapNode<Key> *next = first->sibling_;
        first->parent_ = nullptr;
        first->sibling_ = nullptr;
        BinomialHeap<Key> new_heap(first);
        for (BinomialHeapNode<Key> *i = next; i != nullptr; i = next) {
            BinomialHeapNode<Key> *current = i;
            next = current->sibling_;
            current->sibling_ = nullptr;
            current->parent_ = nullptr;
            new_heap.Merge(*new BinomialHeap(current));
        }
        v->Detach();
        delete v;
        return new_heap;
    }

    template<class Key>
    BinomialHeapNode<Key> *BinomialHeap<Key>::MergeRootsAsLists(BinomialHeapNode<Key> *v1, BinomialHeapNode<Key> *v2) {
        BinomialHeapNode<Key> *cur[] = {v1, v2};
        BinomialHeapNode<Key> *head = nullptr;
        BinomialHeapNode<Key> *current = nullptr;
        while (cur[0] != nullptr && cur[1] != nullptr) {
            int choice = cur[0]->degree_ > cur[1]->degree_;
            if (current != nullptr) {
                current->sibling_ = cur[choice];
            } else {
                head = cur[choice];
            }
            current = cur[choice];
            cur[choice] = cur[choice]->sibling_;
        }

        for (size_t i = 0; i < 2; ++i) {
            while (cur[i] != nullptr) {
                current->sibling_ = cur[i];
                current = cur[i];
                cur[i] = cur[i]->sibling_;
            }
        }
        return head;
    }

    template<class Key>
    void BinomialHeap<Key>::MakeDegreesUnique(BinomialHeapNode<Key> *v) {
        BinomialHeapNode<Key> *previous = nullptr;
        while (v->sibling_ != nullptr) {
            if (v->degree_ == v->sibling_->degree_) {
                if (v->key_ < v->sibling_->key_) {
                    BinomialHeapNode<Key> *next = v->sibling_->sibling_;
                    v->Merge_(v->sibling_);
                    v->sibling_ = next;
                } else {
                    v->sibling_->Merge_(v);
                    v = v->parent_;
                    if (previous != nullptr) {
                        previous->sibling_ = v;
                    }
                }
            } else {
                if (previous != nullptr) {
                    previous->sibling_ = v;
                }
                previous = v;
                v = v->sibling_;
            }
        }
    }

    template<class Key>
    BinomialHeap<Key>::BinomialHeap() : root_(nullptr), is_temporary_(false), size_(0) {}

    template<class Key>
    bool BinomialHeap<Key>::Empty() {
        if (is_temporary_) {
            throw RestrictedMethodException();
        }
        return size_ == 0;
    }

    template<class Key>
    BinomialHeap<Key>::BinomialHeap(BinomialHeapNode<Key> *root) : root_(root), is_temporary_(true), size_(0) {}

    template<class Key>
    void BinomialHeap<Key>::Detach() {
        root_ = nullptr;
        size_ = 0;
    }

    // Destructor
    template<class Key>
    BinomialHeap<Key>::~BinomialHeap<Key>() {
        if (root_ != nullptr) {
            delete root_;
        }
    }

    // Copy constructor
    template<class Key>
    BinomialHeap<Key>::BinomialHeap(const BinomialHeap<Key> &other) : size_(other.size_),
                                                                      root_(new BinomialHeapNode<Key>(*other.root_)) {
        is_temporary_ = other.is_temporary_;
    }

    // Move constructor
    template<class Key>
    BinomialHeap<Key>::BinomialHeap(BinomialHeap<Key> &&other) noexcept {
        root_ = nullptr;
        size_ = 0;
        is_temporary_ = false;
        Swap(other);
    }

    // Copy assignment operator
    template<class Key>
    BinomialHeap<Key> &BinomialHeap<Key>::operator=(const BinomialHeap<Key> &other) {
        if (this != &other) {
            BinomialHeap tmp(other);
            Swap(tmp);
        }
        return *this;
    }

    // Move assignment operator
    template<class Key>
    BinomialHeap<Key> &BinomialHeap<Key>::operator=(BinomialHeap<Key> &&other) noexcept {
        if (this != &other) {
            root_ = nullptr;
            size_ = 0;
            is_temporary_ = false;
            Swap(other);
        }
        return *this;
    }

    template<class Key>
    void BinomialHeap<Key>::Swap(BinomialHeap<Key> &x) noexcept {
        std::swap(root_, x.root_);
        std::swap(size_, x.size_);
    }

    template<class Key>
    std::vector<Key> BinomialHeap<Key>::Data() {
        std::vector<Key> data;
        if (root_ != nullptr) {
            root_->CollectData(data);
        }
        std::sort(data.begin(), data.end());
        return data;
    }
} // namespace heaps

#endif // MERGEABLE_HEAPS_BINOMIAL_H
