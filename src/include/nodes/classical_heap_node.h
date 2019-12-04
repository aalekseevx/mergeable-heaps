#ifndef MERGEABLE_HEAPS_CLASSICAL_HEAP_NODE_H
#define MERGEABLE_HEAPS_CLASSICAL_HEAP_NODE_H

namespace heaps {
// Base class for nodes of simple Mergeable heaps, such as
// leftist heap and skew heap.
    template<class Key, class Derived>
    class ClassicalHeapNode {
    public:
        // Data which will be stored in the node.
        Key key_;
        // Pointers to its children. Equal to nullptr, if there is none.
        Derived *child_left_;
        Derived *child_right_;

        // Simple constructors
        ClassicalHeapNode();
        ClassicalHeapNode(Key key, Derived *child_left, Derived *child_right);

        // Detaches the node from all the others.
        // Children of the detached vertex won't be destroyed after their parent is destroyed.
        void Detach();

        //
        // Rule of Five functions
        //

        // Destructor. Destructs the node and it's subtree.
        ~ClassicalHeapNode();

        // Copy constructor. Creates the copy of the vertex and it's subtree.
        ClassicalHeapNode(const ClassicalHeapNode<Key, Derived> &other);

        // Move constructor. Creates the copy of the vertex by stealing resources.
        // Other vertex is left as newly initialized.
        ClassicalHeapNode(ClassicalHeapNode &&other) noexcept;

        // Copy assignment operator
        ClassicalHeapNode &operator=(const ClassicalHeapNode<Key, Derived> &other);

        // Move assignment operator
        ClassicalHeapNode &operator=(ClassicalHeapNode &&other) noexcept;

        // Swap function for "Copy and Swap" idiom
        void Swap(ClassicalHeapNode &x) noexcept;
    };

    template<class Key, class Derived>
    ClassicalHeapNode<Key, Derived>::~ClassicalHeapNode() {
        if (child_left_ != nullptr) {
            delete child_left_;
        }
        if (child_right_ != nullptr) {
            delete child_right_;
        }
    }

    template<class Key, class Derived>
    ClassicalHeapNode<Key, Derived>::ClassicalHeapNode(const ClassicalHeapNode<Key, Derived> &other) : key_(other.key_),
                                                                                                       child_left_(
                                                                                                               other.child_left_),
                                                                                                       child_right_(
                                                                                                               other.child_right_) {
        if (child_left_ != nullptr) {
            child_left_ = new ClassicalHeapNode(*child_left_);
        }
        if (child_right_ != nullptr) {
            child_right_ = new ClassicalHeapNode(*child_right_);
        }
    }

    template<class Key, class Derived>
    ClassicalHeapNode<Key, Derived>::ClassicalHeapNode(ClassicalHeapNode<Key, Derived> &&other) noexcept {
        child_right_ = child_left_ = nullptr;
        key_ = 0;
        Swap(other);
    }

    template<class Key, class Derived>
    ClassicalHeapNode<Key, Derived> &
    ClassicalHeapNode<Key, Derived>::operator=(const ClassicalHeapNode<Key, Derived> &other) {
        if (this != &other) {
            ClassicalHeapNode tmp(other);
            Swap(tmp);
        }
        return *this;
    }

    template<class Key, class Derived>
    ClassicalHeapNode<Key, Derived> &ClassicalHeapNode<Key, Derived>::operator=(ClassicalHeapNode &&other) noexcept {
        if (this != &other) {
            child_left_ = child_right_ = nullptr;
            key_ = 0;
            Swap(other);
        }
        return *this;
    }

    template<class Key, class Derived>
    ClassicalHeapNode<Key, Derived>::ClassicalHeapNode(Key key, Derived *child_left, Derived *child_right) :
            key_(key), child_left_(child_left), child_right_(child_right) {}

    template<class Key, class Derived>
    void ClassicalHeapNode<Key, Derived>::Swap(ClassicalHeapNode<Key, Derived> &x) noexcept {
        std::swap(child_left_, x.child_left_);
        std::swap(child_right_, x.child_right_);
        std::swap(key_, x.key_);
    }

    template<class Key, class Derived>
    void ClassicalHeapNode<Key, Derived>::Detach() {
        child_left_ = child_right_ = nullptr;
    }

    template<class Key, class Derived>
    ClassicalHeapNode<Key, Derived>::ClassicalHeapNode() : child_left_(nullptr), child_right_(nullptr) {}
} // namespace heaps

#endif // MERGEABLE_HEAPS_CLASSICAL_HEAP_NODE_H
