#ifndef MERGEABLE_HEAPS_BINOMIAL_HEAP_NODE_H
#define MERGEABLE_HEAPS_BINOMIAL_HEAP_NODE_H

namespace heaps {
    // One node of the Binomial Heap. Key is the type of data stored
    template<class Key>
    class BinomialHeapNode {
    public:
        // Stored Data
        Key key_;
        // Links to neighbours
        BinomialHeapNode *parent_;
        BinomialHeapNode *sibling_;
        BinomialHeapNode *child_;
        // Degree - number of children (stored as linked list)
        size_t degree_;

        // Simple constructor
        BinomialHeapNode(Key key, BinomialHeapNode *parent, BinomialHeapNode *sibling, BinomialHeapNode *child,
                         size_t degree) :
                key_(key), parent_(parent), sibling_(sibling), child_(child), degree_(degree) {}

        // Static function, which raises vertex v, i.e.
        // moves from v to its parent while there is a parent
        static void Raise(BinomialHeapNode *&v);

        // Merges two trees in a simple way. *this is the new root.
        void Merge_(BinomialHeapNode *other);

        // Makes a clone of the Node, while not copying the children.
        BinomialHeapNode *Clone();

        //
        // Rule of Five functions
        //

        // Destructor. Destructs the node and it's subtree.
        ~BinomialHeapNode();

        // Copy constructor. Creates the copy of the vertex and it's subtree.
        BinomialHeapNode(const BinomialHeapNode &other);

        // Move constructor. Creates the copy of the vertex by stealing resources.
        // Other vertex is left as newly initialized.
        BinomialHeapNode(BinomialHeapNode &&other) noexcept;

        // Copy assignment operator
        BinomialHeapNode &operator=(const BinomialHeapNode &other);

        // Move assignment operator
        BinomialHeapNode &operator=(BinomialHeapNode &&other) noexcept;

        // Swap function for "Copy and Swap" idiom
        void Swap(BinomialHeapNode &x) noexcept;

        // Recursively scarabs data from the vertex and its children to the std::vector
        void CollectData(std::vector<Key> &x);

        // Detaches the vertex from its neighbours, while
        // not destroying them.
        void Detach();
    };

    template<class Key>
    BinomialHeapNode<Key>::~BinomialHeapNode() {
        if (child_ != nullptr) {
            delete child_;
        }
        if (sibling_ != nullptr) {
            delete sibling_;
        }
    }

    template<class Key>
    BinomialHeapNode<Key>::BinomialHeapNode(const BinomialHeapNode<Key> &other) : key_(other.key_),
                                                                                  parent_(other.parent_),
                                                                                  sibling_(other.sibling_),
                                                                                  child_(other.child_),
                                                                                  degree_(other.degree_) {
        if (child_ != nullptr) {
            child_ = new BinomialHeapNode<Key>(*child_);
        }
        if (sibling_ != nullptr) {
            sibling_ = new BinomialHeapNode<Key>(*sibling_);
        }
    }

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

    template<class Key>
    void BinomialHeapNode<Key>::Detach() {
        parent_ = sibling_ = child_ = nullptr;
    }
} // namespace heaps

#endif // MERGEABLE_HEAPS_BINOMIAL_HEAP_NODE_H
