#ifndef MERGEABLE_HEAPS_CLASSICAL_HEAP_NODE_H
#define MERGEABLE_HEAPS_CLASSICAL_HEAP_NODE_H

// Base class for nodes of simple Mergeable heaps, such as
// leftist heap and skew heap.
template<class Key, class Derived>
class ClassicalHeapNode {
public:
    // Data which will be stored in the node.
    Key key;
    // Pointers to its children. Equal to nullptr, if there is none.
    Derived *child_left;
    Derived *child_right;

    // Simple constructor
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
    if (child_left != nullptr) {
        delete child_left;
    }
    if (child_right != nullptr) {
        delete child_right;
    }
}

template<class Key, class Derived>
ClassicalHeapNode<Key, Derived>::ClassicalHeapNode(const ClassicalHeapNode<Key, Derived> &other) : key(other.key),
                                                                                                   child_left(
                                                                                                           other.child_left),
                                                                                                   child_right(
                                                                                                           other.child_right) {
    if (child_left != nullptr) {
        child_left = new ClassicalHeapNode(*child_left);
    }
    if (child_right != nullptr) {
        child_right = new ClassicalHeapNode(*child_right);
    }
}

template<class Key, class Derived>
ClassicalHeapNode<Key, Derived>::ClassicalHeapNode(ClassicalHeapNode<Key, Derived> &&other) noexcept {
    child_right = child_left = nullptr;
    key = 0;
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
        child_left = child_right = nullptr;
        key = 0;
        Swap(other);
    }
    return *this;
}

template<class Key, class Derived>
ClassicalHeapNode<Key, Derived>::ClassicalHeapNode(Key key, Derived *child_left, Derived *child_right) :
        key(key), child_left(child_left), child_right(child_right) {}

template<class Key, class Derived>
void ClassicalHeapNode<Key, Derived>::Swap(ClassicalHeapNode<Key, Derived> &x) noexcept {
    std::swap(child_left, x.child_left);
    std::swap(child_right, x.child_right);
    std::swap(key, x.key);
}

template<class Key, class Derived>
void ClassicalHeapNode<Key, Derived>::Detach() {
    child_left = child_right = nullptr;
}

#endif //MERGEABLE_HEAPS_CLASSICAL_HEAP_NODE_H
