//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/learned_join/algos/hash_join.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/execution/operator/learned_join/algos/base_merge_and_join_op.hpp"

namespace learned_index {

    class HashJoin: public BaseMergeAndJoinOp<uint64_t> {
        public:
            HashJoin(
                SSTable<uint64_t> *outer, 
                SSTable<uint64_t> *inner, 
                IndexBuilder<uint64_t> *inner_index_builder,
                Comparator<uint64_t> *comparator,
                SSTableBuilder<uint64_t> *result_builder,
                int num_threads):
            BaseMergeAndJoinOp<uint64_t>(outer, inner, inner_index_builder, comparator, result_builder, num_threads) {}

            void preOp() override {
                BaseMergeAndJoinOp<uint64_t>::preOp();
                Iterator<uint64_t> outer_iter(*this->outer_);
                while (outer_iter.valid()) {
                    std::string key(outer_iter.key(), 8);
                    if (outer_hash_map.find(key) == outer_hash_map.end()) {
                        outer_hash_map[key] = 0;
                    }
                    outer_hash_map[key]++;
                    outer_iter.next();
                }
            }

            void doOpOnPartition(Partition partition, TableOpResult<uint64_t> *result) override {
                uint64_t outer_start = partition.outer.first;
                uint64_t outer_end = partition.outer.second;
                uint64_t inner_start = partition.inner.first;
                uint64_t inner_end = partition.inner.second;

                Iterator<uint64_t> outer_iterator(*this->outer_);
                Iterator<uint64_t> inner_iterator(*this->inner_);
                SSTableBuilder<uint64_t> *result_builder = this->result_builder_;

                std::string prev;
                while (inner_iterator.valid()) {
                    std::string key(inner_iterator.key(), 8);
                    if (outer_hash_map.find(key) != outer_hash_map.end() && prev != key) {
                        
                        int repeats = outer_hash_map.at(key);
                        for (int i = 0; i < repeats; i++) {
                            this->result_builder_->add(inner_iterator.key());
                        }
                    }
                    prev = key;
                    inner_iterator.next();
                }
                result->stats["inner_disk_fetch"] = 1;
                result->stats["outer_disk_fetch"] = 1;
                result->output_table = this->result_builder_->build();
            }
        private:
            std::unordered_map<std::string, uint64_t> outer_hash_map;
    };

}