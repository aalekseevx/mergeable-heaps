#ifndef MERGEABLEHEAPS_MERGEABLE_HEAPS_H
#define MERGEABLEHEAPS_MERGEABLE_HEAPS_H

#include "iheap.h"
#include "heaps/binomial.h"
#include "heaps/leftist.h"
#include "heaps/skew.h"
#include "heaps/stl.h"

namespace heaps {
    enum HeapTypes {
            Binomial, Leftist, Skew, STL
    };

    void f() {
        std::set<int> t;
    }

    template <class Key, HeapTypes type=HeapTypes::Skew, class Compare=std::less<Key>>
    class Heap;
}
#endif //MERGEABLEHEAPS_MERGEABLE_HEAPS_H
