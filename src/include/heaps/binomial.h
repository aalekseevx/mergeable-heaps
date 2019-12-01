//#ifndef MERGEABLEHEAPS_BINOMIAL_H
//#define MERGEABLEHEAPS_BINOMIAL_H
//
//template<class T>
//class BinomialNode {
//public:
//    T key;
//    BinomialNode *parent;
//    BinomialNode *sibling;
//    BinomialNode *child;
//    size_t degree;
//    size_t size;
//
//    BinomialNode(T key, BinomialNode *parent, BinomialNode *sibling, BinomialNode *child, size_t degree, size_t size) :
//            key(key), parent(parent), sibling(sibling), child(child), degree(degree), size(size) {}
//
//    void AddSubTree(BinomialNode *p);
//
//    void Raise();
//
//    static BinomialNode *MergeTrees(BinomialNode *p, BinomialNode *q);
//
//    static void MergeSiblingsAsLists(BinomialNode<T> *v1, BinomialNode<T> *v2);
//
//    bool operator< (const BinomialNode<T>& right) const;
//};
//
//template<class T>
//void BinomialNode<T>::AddSubTree(BinomialNode *p) {
//    p->parent = *this;
//    p->sibling = p->child;
//    child = p;
//}
//
//template<class T>
//BinomialNode<T> *BinomialNode<T>::MergeTrees(BinomialNode<T> *p, BinomialNode<T> *q) {
//    if (p == nullptr || q == nullptr) {
//        return p ? p : q;
//    }
//    if (p->key <= q->key) {
//        p->AddSubTree(q);
//        return p;
//    } else {
//        q->AddSubTree(p);
//        return q;
//    }
//}
//
//template<class T>
//bool BinomialNode<T>::operator<(const BinomialNode<T> &right) const {
//    return key < right.key;
//}
//
//template<class T>
//void BinomialNode<T>::Raise() {
//    while (parent != nullptr) {
//        *this = *parent;
//    }
//}
//
//template<class T>
//void BinomialNode<T>*::MergeSiblingsAsLists(BinomialNode<T> *v1, BinomialNode<T> *v2) {
//    BinomialNode<T>* cur
//}
//
//namespace heaps {
//    template<class T>
//    class BinomialHeap : public IHeap<T> {
//    private:
//        BinomialNode<T> *root;
//
//        BinomialNode<T> *FindMinimalBinomialNode();
//
//        void ExtractTopVertex(BinomialNode<T> *v);
//
//        void Merge_(BinomialHeap<T> &x);
//
//        static void MakeDegreesUnique(BinomialNode<T>* v);
//    public:
//        explicit BinomialHeap(int key);
//
//        explicit BinomialHeap();
//
//        void Insert(T x) override;
//
//        T GetMinimum() override;
//
//        void ExtractMinimum() override;
//
//        void Merge(IHeap<T> &x) override;
//
//        size_t Size() override;
//
//        bool Empty() override;
//    };
//
//    template<class T>
//    void BinomialHeap<T>::Insert(T x) {
//        Merge(*new BinomialHeap<T>(x));
//    }
//
//    template<class T>
//    T BinomialHeap<T>::GetMinimum() {
//        return FindMinimalBinomialNode()->key;
//    }
//
//    template<class T>
//    void BinomialHeap<T>::ExtractMinimum() {
//        ExtractTopVertex(FindMinimalBinomialNode());
//    }
//
//    template<class T>
//    void BinomialHeap<T>::Merge_(BinomialHeap<T> &x) {
//        MergeRootsAsLists();
//        MakeDegreesUnique();
//        root->Raise();
//    }
//
//    template<class T>
//    void BinomialHeap<T>::Merge(IHeap<T> &x) {
//        if (&x == this) {
//            return;
//        }
//        try {
//            Merge_(dynamic_cast<BinomialHeap<T> &>(x));
//            x = BinomialHeap<T>();
//        } catch (const std::bad_cast &e) {
//            throw WrongHeapTypeException();
//        }
//    }
//
//    template<class T>
//    BinomialHeap<T>::BinomialHeap(int key) {
//        root = new BinomialNode<T>(key, nullptr, nullptr, nullptr, 0u, 1u);
//    }
//
//    template<class T>
//    size_t BinomialHeap<T>::Size() {
//        return root == nullptr ? 0 : root->size;
//    }
//
//    template<class T>
//    BinomialNode<T> *BinomialHeap<T>::FindMinimalBinomialNode() {
//        if (Empty()) {
//            throw EmptyHeapException();
//        }
//        auto minimum = root;
//        for (auto i = root; i != nullptr; i = i->sibling) {
//            if (*i < *minimum) {
//                minimum = i;
//            }
//        }
//        return minimum;
//    }
//
//    template<class T>
//    bool BinomialHeap<T>::Empty() {
//        return root == nullptr;
//    }
//
//    template<class T>
//    BinomialHeap<T>::BinomialHeap() {
//        root = nullptr;
//    }
//
//    template<class T>
//    void BinomialHeap<T>::ExtractTopVertex(BinomialNode<T> *v) {
//
//    }
//}
//
//#endif //MERGEABLEHEAPS_BINOMIAL_H
