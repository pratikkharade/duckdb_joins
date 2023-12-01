//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/learned_join/duckdb_sstable.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/execution/operator/learned_join/interfaces/sstable.hpp"
#include "duckdb/execution/operator/learned_join/sstable/key_value_slice.hpp"

#include <iostream>
using namespace std;

namespace learned_index {

    class DuckDbSSTable : public SSTable<int> {
        public:
            static void buildDuckDbSSTable(){
                cout << "\n" << "Adding 10";
                SSTable<int>::add(10);
                cout << "\n" << "Adding 20";
                SSTable<int>::add(20);
                cout << "\n" << "Adding 30";
                SSTable<int>::add(30);
                cout << "\n" << "Fetching vector: ";
                vector<int> temp_list = SSTable<int>::getVector();
                for (int x : temp_list)
                    cout << x << " ";
            }
            static bool dummyDuckDbSSTable(){
                cout << "\n" << "DuckDbSStable::dummyDuckDbSStable";
                return true;
            }
    };
}
