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

            void Detach();

            // Rule of Five functions
            ~Node();

            Node(const Node &other);

            Node(Node &&other) noexcept;

            Node &operator=(const Node &other);

            Node &operator=(Node &&other) noexcept;

            void Swap(Node &x) noexcept;
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

        // Rule of Five functions
        ~SkewHeap<Key>();

        SkewHeap<Key>(const SkewHeap<Key> &other);

        SkewHeap<Key>(SkewHeap<Key> &&other) noexcept;

        SkewHeap<Key> &operator=(const SkewHeap<Key> &other);

        SkewHeap<Key> &operator=(SkewHeap<Key> &&other) noexcept;

        void Swap(SkewHeap<Key> &x) noexcept;
    };

    // Destructor
    template<class Key>
    SkewHeap<Key>::Node::~Node() {
        if (child_left != nullptr) {
            delete child_left;
        }
        if (child_right != nullptr) {
            delete child_right;
        }
    }

    // Copy constructor
    template<class Key>
    SkewHeap<Key>::Node::Node(const SkewHeap::Node &other) : key(other.key), child_left(other.child_left),
                                                             child_right(other.child_right) {
        if (child_left != nullptr) {
            child_left = new Node(*child_left);
        }
        if (child_right != nullptr) {
            child_right = new Node(*child_right);
        }
    }

    // Move constructor
    template<class Key>
    SkewHeap<Key>::Node::Node(SkewHeap::Node &&other) noexcept {
        child_right = child_left = nullptr;
        key = 0;
        Swap(other);
    }

    // Copy assignment operator
    template<class Key>
    typename SkewHeap<Key>::Node &SkewHeap<Key>::Node::operator=(const SkewHeap::Node &other) {
        if (this != &other) {
            Node tmp(other);
            Swap(tmp);
        }
        return *this;
    }

    // Move assignment operator
    template<class Key>
    typename SkewHeap<Key>::Node &SkewHeap<Key>::Node::operator=(SkewHeap::Node &&other) noexcept {
        if (this != &other) {
            child_left = child_right = nullptr;
            key = 0;
            Swap(other);
        }
        return *this;
    }

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
    void SkewHeap<Key>::Node::Swap(SkewHeap::Node &x) noexcept {
        std::swap(child_left, x.child_left);
        std::swap(child_right, x.child_right);
        std::swap(key, x.key);
    }

    template<class Key>
    void SkewHeap<Key>::Node::Detach() {
        child_left = child_right = nullptr;
    }

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
            root->Detach();
            delete root;
            root = Node::Merge_(left, right);
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

    // Destructor
    template<class Key>
    SkewHeap<Key>::~SkewHeap<Key>() {
        if (root != nullptr) {
            delete root;
        }
    }

    // Copy constructor
    template<class Key>
    SkewHeap<Key>::SkewHeap(const SkewHeap<Key> &other) : size(other.size), root(new Node(*other.root)) {}

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
