//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/learned_join/algos/sort_join.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include <iostream>
using namespace std;

#include "duckdb/execution/operator/learned_join/algos/base_merge_and_join_op.hpp"

namespace learned_index {

    // template <class T> class SortJoin: public BaseMergeAndJoinOp<T> {
        // public:
            // SortJoin(
            //     SSTable<T> *outer, 
            //     SSTable<T> *inner, 
            //     Comparator<T> *comparator,
            //     PSSTableBuilder<T> *result_builder
					):
            // BaseMergeAndJoinOp<T>(outer, inner, inner_index_builder, comparator, result_builder, num_threads) {}

            // static bool dummyDuckDbSortJoin(){
            //     cout << "\n" << "SortJoin::dummyDuckDbSortJoin";
            //     return true;
            // }

            // void doOpOnPartition(Partition partition, TableOpResult<T> *result) override {
            //     auto result_builder = this->result_builder_->getBuilderForRange(inner_start + outer_start, inner_end + outer_end);

            //     while (outer_iterator->valid()) {
            //         while (inner_iterator->valid() && (this->comparator_->compare(inner_iterator->key(), outer_iterator->key()) < 0)) {
            //             inner_iterator->next();
            //         }
            //         if (!inner_iterator->valid()) {
            //             break;
            //         }
            //         if (this->comparator_->compare(outer_iterator->key(), inner_iterator->key()) == 0) {
            //             result_builder->add(inner_iterator->key());
            //         }
            //         outer_iterator->next();
            //     }
            //     result->output_table = result_builder->build(),
            // };
};
