#ifndef MERGEABLE_HEAPS_SIMPLE_KEY_H
#define MERGEABLE_HEAPS_SIMPLE_KEY_H

// Simple key to store in the heap for testing
class SimpleKey {
public:
    int value_{};

    bool operator<(const SimpleKey &other) const;

    bool operator==(const SimpleKey &other) const;

    SimpleKey &operator=(const SimpleKey &other) = default;
};

bool SimpleKey::operator<(const SimpleKey &other) const {
    return value_ < other.value_;
}

bool SimpleKey::operator==(const SimpleKey &other) const {
    return value_ == other.value_;
}

#endif // MERGEABLE_HEAPS_SIMPLE_KEY_H
