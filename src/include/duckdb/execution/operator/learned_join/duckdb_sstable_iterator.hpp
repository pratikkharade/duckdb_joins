//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/learned_join/duckdb_sstable_iterator.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/execution/operator/learned_join/interfaces/iterator.hpp"
#include "duckdb/execution/operator/learned_join/sstable/key_value_slice.hpp"

#include <iostream>
using namespace std;

namespace learned_index {

    class DuckDbSSTableIterator : public Iterator<int>  {
        public:
            static bool dummyDuckDbSSTableIterator(){
                cout << "\n" << "DuckDbSSTableIterator::dummyDuckDbSSTableIterator";
                return true;
            }
    };
}
