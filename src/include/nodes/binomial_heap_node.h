#ifndef MERGEABLE_HEAPS_BINOMIAL_HEAP_NODE_H
#define MERGEABLE_HEAPS_BINOMIAL_HEAP_NODE_H

namespace heaps {
    template <class Key>
    class BinomialHeapNode {
    public:
        Key key_;
        BinomialHeapNode *parent_;
        BinomialHeapNode *sibling_;
        BinomialHeapNode *child_;
        size_t degree_;

        BinomialHeapNode(Key key, BinomialHeapNode *parent, BinomialHeapNode *sibling, BinomialHeapNode *child, size_t degree) :
                key_(key), parent_(parent), sibling_(sibling), child_(child), degree_(degree) {}

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
        if (child_ != nullptr) {
            delete child_;
        }
        if (sibling_ != nullptr) {
            delete sibling_;
        }
    }

    // Copy constructor
    template<class Key>
    BinomialHeapNode<Key>::BinomialHeapNode(const BinomialHeapNode<Key> &other) : key_(other.key_), parent_(other.parent_),
                                                                                  sibling_(other.sibling_), child_(other.child_),
                                                                                  degree_(other.degree_) {
        if (child_ != nullptr) {
            child_ = new BinomialHeapNode<Key>(*child_);
        }
        if (sibling_ != nullptr) {
            sibling_ = new BinomialHeapNode<Key>(*sibling_);
        }
    }

    // TODO: use detach?
    template<class Key>
    BinomialHeapNode<Key>::BinomialHeapNode(BinomialHeapNode<Key> &&other) noexcept {
        parent_ = sibling_ = child_ = nullptr;
        degree_ = key_ = 0;
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
            parent_ = sibling_ = child_ = nullptr;
            degree_ = key_ = 0;
            Swap(other);
        }
        return *this;
    }

    template<class Key>
    void BinomialHeapNode<Key>::Swap(BinomialHeapNode<Key> &x) noexcept {
        std::swap(key_, x.key_);
        std::swap(parent_, x.parent_);
        std::swap(sibling_, x.sibling_);
        std::swap(child_, x.child_);
        std::swap(degree_, x.degree_);
    }

    template<class Key>
    void BinomialHeapNode<Key>::Raise(BinomialHeapNode<Key> *&v) {
        while (v->parent_ != nullptr) {
            v = v->parent_;
        }
    }

    template<class Key>
    void BinomialHeapNode<Key>::Merge_(BinomialHeapNode<Key> *other) {
        other->parent_ = this;
        other->sibling_ = child_;
        child_ = other;
        ++degree_;
    }

    template<class Key>
    BinomialHeapNode<Key> *BinomialHeapNode<Key>::Clone() {
        return new BinomialHeapNode<Key>(key_, parent_, sibling_, child_, degree_);
    }

    template<class Key>
    void BinomialHeapNode<Key>::CollectData(std::vector<Key> &x) {
        x.push_back(key_);
        if (child_) {
            child_->CollectData(x);
        }
        if (sibling_) {
            sibling_->CollectData(x);
        }
    }
} // namespace heaps

#endif // MERGEABLE_HEAPS_BINOMIAL_HEAP_NODE_H
