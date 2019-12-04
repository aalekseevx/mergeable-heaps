#ifndef MERGEABLE_HEAPS_KEY_H
#define MERGEABLE_HEAPS_KEY_H

class SimpleKey {
public:
    int value{};
    bool operator< (const SimpleKey& other) const;

    bool operator== (const SimpleKey& other) const;

    SimpleKey& operator=(const SimpleKey& other) = default;
};

bool SimpleKey::operator<(const SimpleKey &other) const {
    return value < other.value;
}

bool SimpleKey::operator==(const SimpleKey &other) const {
    return value == other.value;
}

#endif //MERGEABLE_HEAPS_KEY_H
