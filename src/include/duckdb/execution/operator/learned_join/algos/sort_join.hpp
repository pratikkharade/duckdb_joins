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
            //     IndexBuilder<T> *inner_index_builder,
            //     Comparator<T> *comparator,
            //     PSSTableBuilder<T> *result_builder,
            //     int num_threads):
            // BaseMergeAndJoinOp<T>(outer, inner, inner_index_builder, comparator, result_builder, num_threads) {}

            // static bool dummyDuckDbSortJoin(){
            //     cout << "\n" << "SortJoin::dummyDuckDbSortJoin";
            //     return true;
            // }

            // void doOpOnPartition(Partition partition, TableOpResult<T> *result) override {
            //     uint64_t outer_start = partition.outer.first;
            //     uint64_t outer_end = partition.outer.second;
            //     uint64_t inner_start = partition.inner.first;
            //     uint64_t inner_end = partition.inner.second;

            //     auto outer_iterator = this->outer_->getSSTableForSubRange(outer_start, outer_end)->iterator();
            //     auto inner_iterator = this->inner_->getSSTableForSubRange(inner_start, inner_end)->iterator();
            //     auto inner_index = this->inner_index_->getIndexForSubrange(inner_start, inner_end);
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

            //     result->stats["inner_disk_fetch"] = inner_iterator->getDiskFetches();
            //     result->stats["outer_disk_fetch"] = outer_iterator->getDiskFetches();
            //     result->output_table = result_builder->build(),

            //     delete outer_iterator;
            //     delete inner_iterator;
            // };
};