//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/learned_join/algos/partition.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

using namespace learned_index;

#include "duckdb/execution/operator/learned_join/algos/base_merge_and_join_op.hpp"
#include "duckdb/execution/operator/learned_join/interfaces/index.hpp"
#include "duckdb/execution/operator/learned_join/interfaces/sstable.hpp"
#include "duckdb/execution/operator/learned_join/interfaces/comparator.hpp"

namespace learned_index {
    
    struct Partition {
        std::pair<uint64_t, uint64_t> outer;
        std::pair<uint64_t, uint64_t> inner;
    };

    template <class T> std::vector<Partition> partition_sstables(int num_partitions, SSTable<T> outer_table,
        SSTable<T> inner_table, Index<T> *inner_index, Comparator<T> *comparator) {

        std::vector<Partition> partitions;
        Iterator<T> inner_iter(inner_table);
        Iterator<T> outer_iter(outer_table);
        inner_iter.seekToFirst();
        outer_iter.seekToFirst();

        uint64_t num_items = outer_iter.getSize();
        uint64_t block_size = num_items / num_partitions;
        uint64_t spill = num_items % num_partitions;

        uint64_t outer_start = 0;
        uint64_t outer_end = 0;
        uint64_t inner_start = 0;
        uint64_t inner_end = 0;

        for (int i = 0; i < num_partitions; i++) {
            outer_end = outer_start + block_size;
            if (spill) {
                outer_end++;
                spill--;
            }
            uint64_t inner_end =
                inner_index->getPositionBounds(outer_iter.peek(outer_end - 1)).lower;
            while (inner_end < inner_iter.getSize() &&
                comparator->compare(inner_iter.peek(inner_end),
                                    outer_iter.peek(outer_end - 1)) <= 0) {
                inner_end++;
            }
            while (inner_end > 0 &&
                comparator->compare(inner_iter.peek(inner_end - 1),
                                    outer_iter.peek(outer_end - 1)) > 0) {
                inner_end--;
            }
            if (i == num_partitions - 1) {
                inner_end = inner_iter.getSize();
            }
            Comparator<T> *thread_comparator = comparator;
            partitions.push_back(
                Partition{std::pair<uint64_t, uint64_t>(outer_start, outer_end),
                        std::pair<uint64_t, uint64_t>(inner_start, inner_end)});
            outer_start = outer_end;
            inner_start = inner_end;
        }
        return partitions;
    }
}