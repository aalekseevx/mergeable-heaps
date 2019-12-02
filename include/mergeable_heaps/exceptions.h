#ifndef MERGEABLEHEAPS_EXCEPTIONS_H
#define MERGEABLEHEAPS_EXCEPTIONS_H

namespace heaps {
    class WrongHeapTypeException : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "Can't merge different types of heaps";
        }
    };

    class EmptyHeapException : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "Can't access an element of an empty heap";
        }
    };

    class SelfHeapMerge : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "Can't merge a heap to itself. Please, make a copy";
        }
    };
}

#endif //MERGEABLEHEAPS_EXCEPTIONS_H
