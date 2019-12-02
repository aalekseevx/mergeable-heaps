#ifndef MERGEABLEHEAPS_SKEW_H
#define MERGEABLEHEAPS_SKEW_H

#include "iheap.h"
#include "exceptions.h"

namespace heaps {
    template<class Key = int>
    class SkewHeap : public IHeap<Key> {
        class Node {
        public:
            Key key;
            Node *child_left;
            Node *child_right;

            Node(Key key, Node *child_left, Node *child_right);
            static Node *Merge_(Node *root_1, Node *root_2);
        };

        Node *root;
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
    };

    template<class Key>
    typename SkewHeap<Key>::Node *
    SkewHeap<Key>::Node::Merge_(SkewHeap::Node *root_1, SkewHeap::Node *root_2) {
        if (root_1 == nullptr || root_2 == nullptr) {
            return root_1 == nullptr ? root_2 : root_1;
        }
        if (root_1->key > root_2->key) {
            std::swap(root_1, root_2);
        }
        Node *tmp_root = root_1->child_right;
        std::swap(root_1->child_left, root_1->child_right);
        root_1->child_left = Node::Merge_(tmp_root, root_2);
        return root_1;
    }

    template<class Key>
    SkewHeap<Key>::Node::Node(Key key, SkewHeap::Node *child_left, SkewHeap::Node *child_right) :
            key(key), child_left(child_left), child_right(child_right) {}

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
            Node *left = root->child_left;
            Node *right = root->child_right;
            delete root;
            root = Node::Merge_(left, right);
        }
    }

    template<class Key>
    void SkewHeap<Key>::Merge(IHeap <Key> &x) {
        if (&x == this) {
            throw SelfHeapMerge();
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
        root = new Node(key, nullptr, nullptr);
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
        root = Node::Merge_(root, x.root);
    }

    template<class Key>
    SkewHeap<Key>::SkewHeap() : root(nullptr), size(0) {}

    template<class Key>
    void SkewHeap<Key>::Detach() {
        root = nullptr;
        size = 0;
    }
}

#endif //MERGEABLEHEAPS_SKEW_H
