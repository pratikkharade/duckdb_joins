//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/learned_join/interfaces/sstable.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include <iostream>
using namespace std;

namespace learned_index {

    template <class T> class SSTable {
        protected:
            vector<T> table;
        
        public:
            // virtual Iterator<T> *iterator() = 0;
            // virtual Iterator<T> *iterator(int kv_buffer_size, bool aligned) {abort();};
            // virtual SSTable<T> *getSSTableForSubRange(uint64_t start, uint64_t end) = 0;
            
            vector<T> getter() {
                return table;
            }
            void add(T t) {
                table.push_back(t);
            }
            size_t getSize() const {
                return table.size();
            }

            T getElementAt(size_t index) const {
                if (index < table.size()) {
                    return table[index];
                }
                return T();
            }
            void buildSSTable(vector<uint64_t> nums){
                for(uint64_t x : nums){
                    add(x);
                }
            }
    };

    template <class T> class SSTableBuilder {
        public:
            virtual void add(const T &t) = 0;
            virtual SSTable<T> *build() = 0;
    };

    template <class T> class PSSTableBuilder {
        public:
            virtual SSTableBuilder<T> *getBuilderForRange(uint64_t start_index, uint64_t end_index) = 0;
            virtual SSTable<T> *build() = 0;
    };

}
