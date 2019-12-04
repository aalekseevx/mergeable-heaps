#ifndef MERGEABLE_HEAPS_BINOMIAL_HEAP_NODE_H
#define MERGEABLE_HEAPS_BINOMIAL_HEAP_NODE_H

namespace heaps {
    template <class Key>
    class BinomialHeapNode {
    public:
        Key key;
        BinomialHeapNode *parent;
        BinomialHeapNode *sibling;
        BinomialHeapNode *child;
        size_t degree;

        BinomialHeapNode(Key key, BinomialHeapNode *parent, BinomialHeapNode *sibling, BinomialHeapNode *child, size_t degree) :
                key(key), parent(parent), sibling(sibling), child(child), degree(degree) {}

        static void Raise(BinomialHeapNode *&v);

        void Merge_(BinomialHeapNode* other);

        BinomialHeapNode* Clone();

        // Rule of Five functions
        ~BinomialHeapNode();

        BinomialHeapNode(const BinomialHeapNode &other);

        BinomialHeapNode(BinomialHeapNode &&other) noexcept;

        BinomialHeapNode &operator=(const BinomialHeapNode &other);

        BinomialHeapNode &operator=(BinomialHeapNode &&other) noexcept;

        void Swap(BinomialHeapNode &x) noexcept;

        void CollectData(std::vector<Key>& x);
    };

    // Destructor
    template<class Key>
    BinomialHeapNode<Key>::~BinomialHeapNode() {
        if (child != nullptr) {
            delete child;
        }
        if (sibling != nullptr) {
            delete sibling;
        }
    }

    // Copy constructor
    template<class Key>
    BinomialHeapNode<Key>::BinomialHeapNode(const BinomialHeapNode<Key> &other) : key(other.key), parent(other.parent),
                                                                     sibling(other.sibling), child(other.child),
                                                                     degree(other.degree) {
        if (child != nullptr) {
            child = new BinomialHeapNode<Key>(*child);
        }
        if (sibling != nullptr) {
            sibling = new BinomialHeapNode<Key>(*sibling);
        }
    }

    // TODO: use detach?
    template<class Key>
    BinomialHeapNode<Key>::BinomialHeapNode(BinomialHeapNode<Key> &&other) noexcept {
        parent = sibling = child = nullptr;
        degree = key = 0;
        Swap(other);
    }

    template<class Key>
    BinomialHeapNode<Key> &BinomialHeapNode<Key>::operator=(const BinomialHeapNode<Key> &other) {
        if (this != &other) {
            BinomialHeapNode<Key> tmp(other);
            Swap(tmp);
        }
        return *this;
    }

    template<class Key>
    BinomialHeapNode<Key> &BinomialHeapNode<Key>::operator=(BinomialHeapNode<Key> &&other) noexcept {
        if (this != &other) {
            parent = sibling = child = nullptr;
            degree = key = 0;
            Swap(other);
        }
        return *this;
    }

    template<class Key>
    void BinomialHeapNode<Key>::Swap(BinomialHeapNode<Key> &x) noexcept {
        std::swap(key, x.key);
        std::swap(parent, x.parent);
        std::swap(sibling, x.sibling);
        std::swap(child, x.child);
        std::swap(degree, x.degree);
    }

    template<class Key>
    void BinomialHeapNode<Key>::Raise(BinomialHeapNode<Key> *&v) {
        while (v->parent != nullptr) {
            v = v->parent;
        }
    }

    template<class Key>
    void BinomialHeapNode<Key>::Merge_(BinomialHeapNode<Key> *other) {
        other->parent = this;
        other->sibling = child;
        child = other;
        ++degree;
    }

    template<class Key>
    BinomialHeapNode<Key> *BinomialHeapNode<Key>::Clone() {
        return new BinomialHeapNode<Key>(key, parent, sibling, child, degree);
    }

    template<class Key>
    void BinomialHeapNode<Key>::CollectData(std::vector<Key> &x) {
        x.push_back(key);
        if (child) {
            child->CollectData(x);
        }
        if (sibling) {
            sibling->CollectData(x);
        }
    }
}

#endif // MERGEABLE_HEAPS_BINOMIAL_HEAP_NODE_H
