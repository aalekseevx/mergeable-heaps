#ifndef MERGEABLEHEAPS_BINOMIAL_H
#define MERGEABLEHEAPS_BINOMIAL_H

#include "iheap.h"
#include "exceptions.h"
#include <string>

namespace heaps {
    template<class T>
    class BinomialHeap : public IHeap<T> {
    private:
        class Node {
        public:
            T key;
            Node *parent;
            Node *sibling;
            Node *child;
            size_t degree;
            size_t size;

            Node (T key, Node *parent, Node *sibling, Node *child, size_t degree, size_t size) :
            key(key), parent(parent), sibling(sibling), child(child), degree(degree), size(size) {}
        };

        Node *root;

        std::tuple<T, Node *> FindMinimalNode();

        void ExtractTopVertex(Node *v);

        BinomialHeap<T> CutVertex(Node *v);

        void Merge_(BinomialHeap<T> &x);

        Node* MergeRootsAsLists(Node *v1, Node *v2);

        static void MakeDegreesUnique(Node* v);

        static BinomialHeap<T> MakeHeap(Node* v);

    public:
        explicit BinomialHeap(int key);

        explicit BinomialHeap();

        void Insert(T x) override;

        T GetMinimum() override;

        void ExtractMinimum() override;

        void Merge(IHeap<T> &x) override;

        size_t Size() override;

        bool Empty() override;
    };

    template<class T>
    void BinomialHeap<T>::Insert(T x) {
        Merge(*new BinomialHeap<T>(x));
    }

    template<class T>
    T BinomialHeap<T>::GetMinimum() {
        return std::get<0>(FindMinimalNode());
    }

    template<class T>
    void BinomialHeap<T>::ExtractTopVertex(Node *v) {
        Node *predecessor = nullptr;
        for (Node *i = root; i != v; i = i->sibling) {
            i->size -= v->size;
            predecessor = i;
        }
        if (predecessor == nullptr) {
            root = v->sibling;
        } else {
            predecessor->sibling = v->sibling;
        }
        Merge(*new BinomialHeap<T>(CutVertex(v)));
    }

    template<class T>
    void BinomialHeap<T>::ExtractMinimum() {
        Node *minimal_node = std::get<1>(FindMinimalNode());
        ExtractTopVertex(minimal_node);
    }

    template<class T>
    void BinomialHeap<T>::Merge_(BinomialHeap<T> &x) {
        if (root == nullptr || x.root == nullptr) {
            root = root == nullptr ? x.root : root;
            return;
        }
        root = MergeRootsAsLists(root, x.root);
        MakeDegreesUnique(root);
        while (root->parent != nullptr) {
            root = root->parent;
        }
        x = BinomialHeap<T>();
    }

    template<class T>
    void BinomialHeap<T>::Merge(IHeap<T> &x) {
        if (&x == this) {
            throw SelfHeapMerge();
        }
        try {
            Merge_(dynamic_cast<BinomialHeap<T> &>(x));
        } catch (const std::bad_cast &e) {
            throw WrongHeapTypeException();
        }
    }

    template<class T>
    BinomialHeap<T>::BinomialHeap(int key) {
        root = new Node(key, nullptr, nullptr, nullptr, 0u, 1u);
    }

    template<class T>
    size_t BinomialHeap<T>::Size() {
        return root == nullptr ? 0 : root->size;
    }

    template<class T>
    std::tuple<T, typename BinomialHeap<T>::Node *> BinomialHeap<T>::FindMinimalNode() {
        if (root == nullptr) {
            throw EmptyHeapException();
        }
        T minimum = root->key;
        Node *minimal_node = root;
        for (Node *i = root; i != nullptr; i = i->sibling) {
            if (i->key < minimum) {
                minimum = i->key;
                minimal_node = i;
            }
        }
        return std::make_tuple(minimum, minimal_node);
    }

    template<class T>
    BinomialHeap<T> BinomialHeap<T>::CutVertex(BinomialHeap::Node *v) {
        auto new_heap = MakeHeap(v->child);
        for (Node *i = v->child; i != nullptr; i = i->sibling) {
            i->parent = nullptr;
        }
        return new_heap;
    }

    template<class T>
    typename BinomialHeap<T>::Node* BinomialHeap<T>::MergeRootsAsLists(BinomialHeap::Node *v1, BinomialHeap::Node *v2) {
        Node* cur[] = {v1, v2};
        Node* head = nullptr;
        Node* current = nullptr;
        while (cur[0] != nullptr && cur[1] != nullptr) {
            int choice = cur[0]->degree < cur[1]->degree;
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

    template<class T>
    void BinomialHeap<T>::MakeDegreesUnique(Node* v) {
        Node* previous = nullptr;
        while (v->sibling != nullptr) {
            if (v->degree == v->sibling->degree) {
                if (v->key < v->sibling->key) {
                    if (previous != nullptr) {
                        previous->sibling = v;
                    }
                    previous = v;

                    Node* tmp = new Node(*v->sibling);
                    tmp->sibling = v->child;
                    tmp->parent = v;
                    v->child = tmp;
                } else {
                    if (previous != nullptr) {
                        previous->sibling = v->sibling;
                    }
                    previous = v->sibling;

                    Node* tmp = new Node(*v);
                    tmp->sibling = v->sibling->child;
                    tmp->parent = v->sibling;
                    v->sibling->child = tmp;
                }
            } else {
                v = v->sibling;
            }
        }
    }

    template<class T>
    BinomialHeap<T>::BinomialHeap() : root(nullptr) {}

    template<class T>
    BinomialHeap<T> BinomialHeap<T>::MakeHeap(BinomialHeap::Node *v) {
        BinomialHeap heap;
        heap.root = v;
        return heap;
    }

    template<class T>
    bool BinomialHeap<T>::Empty() {

    }
}

#endif //MERGEABLEHEAPS_BINOMIAL_H
