#ifndef MERGEABLEHEAPS_BINOMIAL_H
#define MERGEABLEHEAPS_BINOMIAL_H

#include "iheap.h"
#include "exceptions.h"
#include <string>

namespace heaps {
    template<class Key>
    class BinomialHeap : public IHeap<Key> {
    private:
        class Node {
        public:
            Key key;
            Node *parent;
            Node *sibling;
            Node *child;
            size_t degree;
            Node (Key key, Node *parent, Node *sibling, Node *child, size_t degree) :
            key(key), parent(parent), sibling(sibling), child(child), degree(degree) {}
            static void Raise(Node*& v);
            size_t CalculateSize();

            // Rule of Five functions
            ~Node();
            Node(const Node& other);
            Node(Node&& other) noexcept;
            const Node& operator=(const Node& other);
            const Node& operator=(Node&& other) noexcept;

            void Swap(Node& x) noexcept;
        };

        Node *root;
        size_t size;

        std::tuple<Key, Node *> FindMinimalNode();

        void ExtractTopVertex(Node *v);

        BinomialHeap<Key> CutVertex(Node *v);

        void Merge_(BinomialHeap<Key> &x);

        Node* MergeRootsAsLists(Node *v1, Node *v2);

        static void MakeDegreesUnique(Node* v);

        explicit BinomialHeap(Node*);

        void Detach() override;
    public:

        explicit BinomialHeap(int key);

        explicit BinomialHeap();

        void Insert(Key x) override;

        Key GetMinimum() override;

        void ExtractMinimum() override;

        void Merge(IHeap<Key> &x) override;

        size_t Size() override;

        bool Empty() override;

        // Rule of Five functions
        ~BinomialHeap<Key>();
        BinomialHeap<Key>(const BinomialHeap<Key>& other);
        BinomialHeap<Key>(BinomialHeap<Key>&& other) noexcept;
        const BinomialHeap<Key>& operator=(const BinomialHeap<Key>& other);
        const BinomialHeap<Key>& operator=(BinomialHeap<Key>&& other) noexcept;

        void Swap(BinomialHeap<Key>& x) noexcept;
    };

    template<class Key>
    size_t BinomialHeap<Key>::Node::CalculateSize() {
        return 1 +
                (sibling == nullptr ? 0 : sibling->CalculateSize()) +
                (child == nullptr ? 0 : child->CalculateSize());
    }

    template<class Key>
    BinomialHeap<Key>::Node::~Node() {
        delete child;
        delete sibling;
    }

    // Copy constructor
    template<class Key>
    BinomialHeap<Key>::Node::Node(const BinomialHeap::Node &other) : key(other.key), parent(other.parent),
    sibling(other.sibling), child(other.child), degree(other.degree) {
        if (child) {
            child = new Node(*child);
        }
        if (sibling) {
            sibling = new Node(*sibling);
        }
    }

    // Move constructor
    template<class Key>
    BinomialHeap<Key>::Node::Node(BinomialHeap::Node &&other) noexcept {
        *this = Node();
        Swap(other);
    }

    // Copy assignment operator
    template<class Key>
    const typename BinomialHeap<Key>::Node &BinomialHeap<Key>::Node::operator=(const BinomialHeap::Node &other) {
        if (this != &other) {
            Node tmp(other);
            Swap(tmp);
        }
        return *this;
    }

    // Move assignment operator
    template<class Key>
    const typename BinomialHeap<Key>::Node &BinomialHeap<Key>::Node::operator=(BinomialHeap::Node &&other) noexcept {
        if (this != &other) {
            Swap(other);
        }
        return *this;
    }

    template<class Key>
    void BinomialHeap<Key>::Node::Swap(BinomialHeap::Node &x) noexcept {

    }

    template<class Key>
    void BinomialHeap<Key>::Node::Raise(BinomialHeap::Node *&v) {
        while (v->parent != nullptr) {
            v = v->parent;
        }
    }

    template<class Key>
    void BinomialHeap<Key>::Insert(Key x) {
        Merge(*new BinomialHeap<Key>(x));
    }

    template<class Key>
    Key BinomialHeap<Key>::GetMinimum() {
        return std::get<0>(FindMinimalNode());
    }

    template<class Key>
    void BinomialHeap<Key>::ExtractTopVertex(Node *v) {
        Node *predecessor = nullptr;
        for (Node *i = root; i != v; i = i->sibling) {
            predecessor = i;
        }
        if (predecessor == nullptr) {
            root = v->sibling;
        } else {
            predecessor->sibling = v->sibling;
        }
        Merge(*new BinomialHeap<Key>(CutVertex(v)));
    }

    template<class Key>
    void BinomialHeap<Key>::ExtractMinimum() {
        ExtractTopVertex(std::get<1>(FindMinimalNode()));
    }

    template<class Key>
    void BinomialHeap<Key>::Merge_(BinomialHeap<Key> &x) {
        if (root == nullptr || x.root == nullptr) {
            root = root == nullptr ? x.root : root;
            return;
        }
        root = MergeRootsAsLists(root, x.root);
        MakeDegreesUnique(root);
        Node::Raise(root);
    }

    template<class Key>
    void BinomialHeap<Key>::Merge(IHeap<Key> &x) {
        if (&x == this) {
            throw SelfHeapMerge();
        }
        try {
            Merge_(dynamic_cast<BinomialHeap<Key> &>(x));
            x.Detach();
        } catch (const std::bad_cast &e) {
            throw WrongHeapTypeException();
        }
    }

    template<class Key>
    BinomialHeap<Key>::BinomialHeap(int key) : size(1) {
        root = new Node(key, nullptr, nullptr, nullptr, 0u);
    }

    template<class Key>
    size_t BinomialHeap<Key>::Size() {
        return size;
    }

    template<class Key>
    std::tuple<Key, typename BinomialHeap<Key>::Node *> BinomialHeap<Key>::FindMinimalNode() {
        if (root == nullptr) {
            throw EmptyHeapException();
        }
        Key minimum = root->key;
        Node *minimal_node = root;
        for (Node *i = root; i != nullptr; i = i->sibling) {
            if (i->key < minimum) {
                minimum = i->key;
                minimal_node = i;
            }
        }
        return std::make_tuple(minimum, minimal_node);
    }

    template<class Key>
    BinomialHeap<Key> BinomialHeap<Key>::CutVertex(BinomialHeap::Node *v) {
        BinomialHeap<Key> new_heap(v->child);
        for (Node *i = v->child; i != nullptr; i = i->sibling) {
            i->parent = nullptr;
        }
        return new_heap;
    }

    template<class Key>
    typename BinomialHeap<Key>::Node* BinomialHeap<Key>::MergeRootsAsLists(BinomialHeap::Node *v1, BinomialHeap::Node *v2) {
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

    template<class Key>
    void BinomialHeap<Key>::MakeDegreesUnique(Node* v) {
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

    template<class Key>
    BinomialHeap<Key>::BinomialHeap() : root(nullptr), size(0) {}

    template<class Key>
    bool BinomialHeap<Key>::Empty() {
        return size == 0;
    }

    template<class Key>
    BinomialHeap<Key>::BinomialHeap(BinomialHeap::Node *root) : root(root) {
        size = root->CalculateSize();
    }

    template<class Key>
    void BinomialHeap<Key>::Detach() {
        root = nullptr;
        size = 0;
    }

    // Destructor
    template<class Key>
    BinomialHeap<Key>::~BinomialHeap<Key>() {
        delete root;
    }

    // Copy constructor
    template<class Key>
    BinomialHeap<Key>::BinomialHeap(const BinomialHeap<Key> &other) : size(other.size), root(other.root) {}

    // Move constructor
    template<class Key>
    BinomialHeap<Key>::BinomialHeap(BinomialHeap<Key> &&other) noexcept {
        *this = BinomialHeap();
        Swap(other);
    }

    // Copy assignment operator
    template<class Key>
    const BinomialHeap<Key> &BinomialHeap<Key>::operator=(const BinomialHeap<Key> &other) {
        if (this != &other) {
            BinomialHeap tmp(other);
            Swap(tmp);
        }
        return *this;
    }

    // Move assignment operator
    template<class Key>
    const BinomialHeap<Key> &BinomialHeap<Key>::operator=(BinomialHeap<Key> &&other) noexcept {
        if (this != &other) {
            Swap(other);
        }
        return *this;
    }

    template<class Key>
    void BinomialHeap<Key>::Swap(BinomialHeap<Key> &x) noexcept {
        std::swap(root, x.root);
        std::swap(size, x.size);
    }
}

#endif //MERGEABLEHEAPS_BINOMIAL_H
