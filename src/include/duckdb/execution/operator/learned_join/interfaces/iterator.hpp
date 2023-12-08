//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/learned_join/interfaces/iterator.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/execution/operator/learned_join/interfaces/sstable.hpp"

#include <iostream>
using namespace std;

namespace learned_index {

    template <class T> class Iterator {
        protected:
            const SSTable<T>& sstableRef;
            uint64_t currentIndex;
        
        public:
            // virtual bool valid() = 0;
            // virtual void next() = 0;
            // virtual T peek(uint64_t pos) = 0;
            // virtual void seekToFirst() = 0;
            // virtual T key() = 0;
            // virtual uint64_t currentPos() = 0;
            // virtual uint64_t numElts() = 0;
            // virtual bool keyIsPresent(uint64_t lower, uint64_t pos, uint64_t upper, T key) = 0;
            // // STATS.
            // virtual uint64_t getDiskFetches() { return 0; };

            Iterator(const SSTable<T>& sstableObj) : sstableRef(sstableObj), currentIndex(0) {}

            bool valid() const {
                return currentIndex < sstableRef.getSize();
            }
            void next() {
                currentIndex++;
            }
            T peek(uint64_t pos) {
                if(pos < sstableRef.getSize()){
                    return sstableRef.getElementAt(pos);
                }
                return T();
            }
            void seekToFirst() {
                currentIndex = 0;
            }
            uint64_t getSize() {
                return sstableRef.getSize();
            }
            T key() {
                return sstableRef.getElementAt(currentIndex);
            }
            uint64_t currentPos() {
                return currentIndex;
            }
            uint64_t getDiskFetches() { 
                return 0; 
            }
    };
}
