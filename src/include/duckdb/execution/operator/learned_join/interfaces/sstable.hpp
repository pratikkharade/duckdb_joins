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

#include "duckdb/execution/operator/learned_join/interfaces/iterator.hpp"

namespace learned_index {

    template <class T> class SSTable {
        protected:
            static vector<T> nums;
        
        public:
            static bool dummySSTable(){
                cout << "\n" << "SSTable::dummySStable";
                return true;
            }
            virtual Iterator<T> *iterator() = 0;
            virtual Iterator<T> *iterator(int kv_buffer_size, bool aligned) {abort();};
            virtual SSTable<T> *getSSTableForSubRange(uint64_t start, uint64_t end) = 0;
            
            static vector<T> getVector(){
                return nums;
            }
            static void add(T t){
                nums.push_back(t);
            }
        
        
    };

    template <class T> vector<T> SSTable<T>::nums;

    template <class T> class SSTableBuilder {
        public:
            static bool dummySSTableBuilder(){
                cout << "\n" << "SSTableBuilder::dummySSTableBuilder";
                return true;
            }
            virtual SSTable<T> *build() = 0;
    };

    template <class T> class PSSTableBuilder {
        public:
            virtual SSTableBuilder<T> *getBuilderForRange(uint64_t start_index, uint64_t end_index) = 0;
            virtual SSTable<T> *build() = 0;
    };
}
