#ifndef MERGEABLEHEAPS_LEFTIST_H
#define MERGEABLEHEAPS_LEFTIST_H

#include "iheap.h"

namespace heaps {
    template<class Key=int>
    class LeftistHeap : public IHeap<Key> {
    private:
        class Node {
        public:
            Key key;
            Node *child_left;
            Node *child_right;
            size_t rank;

            Node(Key key, Node *child_left, Node *child_right, size_t rank);

            void UpdateRank();

            static Node *Merge_(Node *root_1, Node *root_2);
        };

        Node *root;
        size_t size;
    public:
        explicit LeftistHeap(Key key);

        LeftistHeap();

        void Insert(Key x) override;

        Key GetMinimum() override;

        void ExtractMinimum() override;

        void Merge(IHeap <Key> &x) override;

        size_t Size() override;

        bool Empty() override;

        void Merge_(LeftistHeap &x);

        void Detach() override;
    };

    template<class Key>
    typename LeftistHeap<Key>::Node *
    LeftistHeap<Key>::Node::Merge_(LeftistHeap::Node *root_1, LeftistHeap::Node *root_2) {
        if (root_1 == nullptr || root_2 == nullptr) {
            return root_1 == nullptr ? root_2 : root_1;
        }
        if (root_1->key > root_2->key) {
            std::swap(root_1, root_2);
        }

        root_1->child_right = Merge_(root_1->child_right, root_2);

        if (root_1->child_left == nullptr || root_1->child_left->rank < root_1->child_right->rank) {
            std::swap(root_1->child_left, root_1->child_right);
        }
        root_1->UpdateRank();

        return root_1;
    }

    template<class Key>
    LeftistHeap<Key>::Node::Node(Key key, LeftistHeap::Node *child_left, LeftistHeap::Node *child_right, size_t rank) :
            key(key), child_left(child_left), child_right(child_right), rank(rank) {}

    template<class Key>
    void LeftistHeap<Key>::Node::UpdateRank() {
        rank = 1 + std::min(
                (child_left == nullptr ? 0 : child_left->rank),
                (child_right == nullptr ? 0 : child_right->rank)
                );
    }

    template<class Key>
    void LeftistHeap<Key>::Insert(Key x) {
        Merge(*new LeftistHeap(x));
    }

    template<class Key>
    Key LeftistHeap<Key>::GetMinimum() {
        if (Empty()) {
            throw EmptyHeapException();
        } else {
            return root->key;
        }
    }

    template<class Key>
    void LeftistHeap<Key>::ExtractMinimum() {
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
    void LeftistHeap<Key>::Merge(IHeap <Key> &x) {
        if (&x == this) {
            throw SelfHeapMerge();
        }
        try {
            Merge_(dynamic_cast<LeftistHeap<Key> &>(x));
            x.Detach();
        } catch (const std::bad_cast &e) {
            throw WrongHeapTypeException();
        }
    }

    template<class Key>
    LeftistHeap<Key>::LeftistHeap(Key key) : size(1) {
        root = new Node(key, nullptr, nullptr, 1);
    }

    template<class Key>
    size_t LeftistHeap<Key>::Size() {
        return Empty() ? 0 : size;
    }

    template<class Key>
    bool LeftistHeap<Key>::Empty() {
        return root == nullptr;
    }

    template<class Key>
    void LeftistHeap<Key>::Merge_(LeftistHeap &x) {
        root = Node::Merge_(root, x.root);
    }

    template<class Key>
    LeftistHeap<Key>::LeftistHeap() : root(nullptr), size(0) {}

    template<class Key>
    void LeftistHeap<Key>::Detach() {
        root = nullptr;
        size = 0;
    }
}

#endif //MERGEABLEHEAPS_LEFTIST_H
