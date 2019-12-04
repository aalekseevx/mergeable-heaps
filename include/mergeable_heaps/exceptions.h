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

    class SelfHeapMergeException : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "Can't merge a heap to itself. Please, make a copy";
        }
    };

    class RestrictedMethodException : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "This method is restricted, because the result can't be relied on.";
        }
    };
}

#endif //MERGEABLEHEAPS_EXCEPTIONS_H
