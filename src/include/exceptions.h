#ifndef MERGEABLEHEAPS_EXCEPTIONS_H
#define MERGEABLEHEAPS_EXCEPTIONS_H

class WrongHeapTypeException : public std::exception {
    [[nodiscard]] const char* what () const noexcept override
    {
        return "Can't merge different types of heaps";
    }
};

#endif //MERGEABLEHEAPS_EXCEPTIONS_H
