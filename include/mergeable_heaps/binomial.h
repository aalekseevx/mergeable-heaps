#ifndef MERGEABLE_HEAPS_BINOMIAL_H
#define MERGEABLE_HEAPS_BINOMIAL_H

#include <string>
#include <algorithm>
#include "iheap.h"
#include "exceptions.h"
#include "nodes/binomial_heap_node.h"

namespace heaps {
    template<class Key>
    class BinomialHeap : public IHeap<Key> {
    private:
        BinomialHeapNode<Key> *root;

        // As we save memory and don't store size of the subtree in BinomialHeapNode<Key>s,
        // some heaps, created by Merge might not contain size information.
        // They will throw a RestrictedMethodException
        bool is_temporary;
        size_t size;

        BinomialHeapNode<Key> *FindMinimalNode();

        void ExtractTopVertex(BinomialHeapNode<Key> *v);

        BinomialHeap<Key> CutVertex(BinomialHeapNode<Key> *v);

        void Merge_(BinomialHeap<Key> &x);

        BinomialHeapNode<Key> *MergeRootsAsLists(BinomialHeapNode<Key> *v1, BinomialHeapNode<Key> *v2);

        static void MakeDegreesUnique(BinomialHeapNode<Key> *v);

        explicit BinomialHeap(BinomialHeapNode<Key> *);

        void Detach() override;

    public:

        explicit BinomialHeap(Key key);

        explicit BinomialHeap();

        void Insert(Key x) override;

        Key GetMinimum() override;

        void ExtractMinimum() override;

        void Merge(IHeap<Key> &x) override;

        size_t Size() override;

        bool Empty() override;

        std::vector<Key> Data();

        // Rule of Five functions
        ~BinomialHeap<Key>();

        BinomialHeap<Key>(const BinomialHeap<Key> &other);

        BinomialHeap<Key>(BinomialHeap<Key> &&other) noexcept;

        BinomialHeap<Key> &operator=(const BinomialHeap<Key> &other);

        BinomialHeap<Key> &operator=(BinomialHeap<Key> &&other) noexcept;

        void Swap(BinomialHeap<Key> &x) noexcept;
    };

    template<class Key>
    void BinomialHeap<Key>::Insert(Key x) {
        Merge(*new BinomialHeap<Key>(x));
    }

    template<class Key>
    Key BinomialHeap<Key>::GetMinimum() {
        return FindMinimalNode()->key;
    }

    template<class Key>
    void BinomialHeap<Key>::ExtractTopVertex(BinomialHeapNode<Key> *v) {
        BinomialHeapNode<Key> *predecessor = nullptr;
        for (BinomialHeapNode<Key> *i = root; i != v; i = i->sibling) {
            predecessor = i;
        }
        if (predecessor == nullptr) {
            root = v->sibling;
        } else {
            predecessor->sibling = v->sibling;
        }
        Merge(*new BinomialHeap<Key>(CutVertex(v)));
        // Decreasing size and disabling restricting
        size -= 1;
        is_temporary = false;
    }

    template<class Key>
    void BinomialHeap<Key>::ExtractMinimum() {
        ExtractTopVertex(FindMinimalNode());
    }

    template<class Key>
    void BinomialHeap<Key>::Merge_(BinomialHeap<Key> &x) {
        if (root == nullptr || x.root == nullptr) {
            root = root == nullptr ? x.root : root;
            return;
        }
        root = MergeRootsAsLists(root, x.root);
        MakeDegreesUnique(root);
        BinomialHeapNode<Key>::Raise(root);
    }

    template<class Key>
    void BinomialHeap<Key>::Merge(IHeap<Key> &x) {
        if (&x == this) {
            throw SelfHeapMergeException();
        }
        try {
            auto& casted = dynamic_cast<BinomialHeap<Key> &>(x);
            Merge_(casted);
            // Trying to update size.
            // If merged heap was temporary, we can't rely on the size field again.
            try {
                size += casted.Size();
            } catch (const RestrictedMethodException &e) {
                is_temporary = true;
            }
            x.Detach();
        } catch (const std::bad_cast &e) {
            throw WrongHeapTypeException();
        }
    }

    template<class Key>
    BinomialHeap<Key>::BinomialHeap(Key key) : size(1), is_temporary(false) {
        root = new BinomialHeapNode<Key>(key, nullptr, nullptr, nullptr, 0u);
    }

    template<class Key>
    size_t BinomialHeap<Key>::Size() {
        if (is_temporary) {
            throw RestrictedMethodException();
        }
        return size;
    }

    template<class Key>
    BinomialHeapNode<Key> *BinomialHeap<Key>::FindMinimalNode() {
        if (root == nullptr) {
            throw EmptyHeapException();
        }
        BinomialHeapNode<Key> *minimal_node = root;
        for (BinomialHeapNode<Key> *i = root; i != nullptr; i = i->sibling) {
            if (i->key < minimal_node->key) {
                minimal_node = i;
            }
        }
        return minimal_node;
    }

    // TODO DetachSibling
    template<class Key>
    BinomialHeap<Key> BinomialHeap<Key>::CutVertex(BinomialHeapNode<Key> *v) {
        BinomialHeapNode<Key>* first = v->child;
        if (first == nullptr) {
            return BinomialHeap<Key>();
        }
        BinomialHeapNode<Key>* next = first->sibling;
        first->parent = nullptr;
        first->sibling = nullptr;
        BinomialHeap<Key> new_heap(first);
        for (BinomialHeapNode<Key> *i = next; i != nullptr; i = next) {
            BinomialHeapNode<Key>* current = i;
            next = current->sibling;
            current->sibling = nullptr;
            current->parent = nullptr;
            new_heap.Merge(*new BinomialHeap(current));
        }
        v->child = nullptr;
        return new_heap;
    }

    template<class Key>
    BinomialHeapNode<Key> *BinomialHeap<Key>::MergeRootsAsLists(BinomialHeapNode<Key> *v1, BinomialHeapNode<Key> *v2) {
        BinomialHeapNode<Key> *cur[] = {v1, v2};
        BinomialHeapNode<Key> *head = nullptr;
        BinomialHeapNode<Key> *current = nullptr;
        while (cur[0] != nullptr && cur[1] != nullptr) {
            int choice = cur[0]->degree > cur[1]->degree;
            if (current != nullptr) {
                current->sibling = cur[choice];
            } else {
                head = cur[choice];
            }
            current = cur[choice];
            cur[choice] = cur[choice]->sibling;
        }

        for (size_t i = 0; i < 2; ++i) {
            while (cur[i] != nullptr) {
                current->sibling = cur[i];
                current = cur[i];
                cur[i] = cur[i]->sibling;
            }
        }
        return head;
    }

    template<class Key>
    void BinomialHeap<Key>::MakeDegreesUnique(BinomialHeapNode<Key> *v) {
        BinomialHeapNode<Key> *previous = nullptr;
        while (v->sibling != nullptr) {
            if (v->degree == v->sibling->degree) {
                if (v->key < v->sibling->key) {
                    BinomialHeapNode<Key> *next = v->sibling->sibling;
                    v->Merge_(v->sibling);
                    v->sibling = next;
                } else {
                    v->sibling->Merge_(v);
                    v = v->parent;
                    if (previous != nullptr) {
                        previous->sibling = v;
                    }
                }
            } else {
                if (previous != nullptr) {
                    previous->sibling = v;
                }
                previous = v;
                v = v->sibling;
            }
        }
    }

    template<class Key>
    BinomialHeap<Key>::BinomialHeap() : root(nullptr), is_temporary(false), size(0) {}

    template<class Key>
    bool BinomialHeap<Key>::Empty() {
        if (is_temporary) {
            throw RestrictedMethodException();
        }
        return size == 0;
    }

    template<class Key>
    BinomialHeap<Key>::BinomialHeap(BinomialHeapNode<Key>* root) : root(root), is_temporary(true), size(0) {}

    template<class Key>
    void BinomialHeap<Key>::Detach() {
        root = nullptr;
        size = 0;
    }

    // Destructor
    template<class Key>
    BinomialHeap<Key>::~BinomialHeap<Key>() {
        if (root != nullptr) {
            delete root;
        }
    }

    // Copy constructor
    template<class Key>
    BinomialHeap<Key>::BinomialHeap(const BinomialHeap<Key> &other) : size(other.size), root(new BinomialHeapNode<Key>(*other.root)) {
        is_temporary = other.is_temporary;
    }

    // Move constructor
    template<class Key>
    BinomialHeap<Key>::BinomialHeap(BinomialHeap<Key> &&other) noexcept {
        root = nullptr;
        size = 0;
        is_temporary = false;
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
            root = nullptr;
            size = 0;
            is_temporary = false;
            Swap(other);
        }
        return *this;
    }

    template<class Key>
    void BinomialHeap<Key>::Swap(BinomialHeap<Key> &x) noexcept {
        std::swap(root, x.root);
        std::swap(size, x.size);
    }

    template<class Key>
    std::vector<Key> BinomialHeap<Key>::Data() {
        std::vector<Key> data;
        if (root != nullptr) {
            root->CollectData(data);
        }
        std::sort(data.begin(), data.end());
        return data;
    }
} // namespace heaps

#endif //MERGEABLE_HEAPS_BINOMIAL_H
