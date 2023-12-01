//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/learned_join/duckdb_sstable_builder.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/execution/operator/learned_join/interfaces/sstable.hpp"
#include "duckdb/execution/operator/learned_join/sstable/key_value_slice.hpp"

#include <iostream>
using namespace std;

namespace learned_index {

    class DuckDbSSTableBuilder : public SSTableBuilder<int> {
        public:
            static bool dummyDuckDbSSTableBuilder(){
                cout << "\n" << "DuckDbSSTableBuilder::dummyDuckDbSSTableBuilder";
                return true;
            }
    };
}