//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/learned_join/interfaces/iterator.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include <iostream>
using namespace std;

namespace learned_index {

    template <class T> class Iterator {
        public:
            static bool dummySSTableIterator(){
                cout << "\n" << "SSTableIterator::dummySSTableIterator";
                return true;
            }
            virtual bool valid() = 0;
            virtual void next() = 0;
            virtual T peek(uint64_t pos) = 0;
            virtual void seekToFirst() = 0;
            virtual T key() = 0;
            virtual uint64_t currentPos() = 0;
            virtual uint64_t numElts() = 0;
            virtual bool keyIsPresent(uint64_t lower, uint64_t pos, uint64_t upper, T key) = 0;
            // STATS.
            virtual uint64_t getDiskFetches() { return 0; };
    };
}
