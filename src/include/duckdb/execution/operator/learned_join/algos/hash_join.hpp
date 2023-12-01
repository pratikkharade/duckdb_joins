//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/learned_join/algos/hash_join.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include <iostream>
using namespace std;

#include "duckdb/execution/operator/learned_join/algos/base_merge_and_join_op.hpp"

namespace learned_index {

    // class HashJoin: public BaseMergeAndJoinOp<KVSlice> {
    //     public:
    //         HashJoin(
    //             SSTable<KVSlice> *outer, 
    //             SSTable<KVSlice> *inner, 
    //             IndexBuilder<KVSlice> *inner_index_builder,
    //             Comparator<KVSlice> *comparator,
    //             PSSTableBuilder<KVSlice> *result_builder,
    //             int num_threads):
    //         BaseMergeAndJoinOp<KVSlice>(outer, inner, inner_index_builder, comparator, result_builder, num_threads) {}

    //         static bool dummyDuckDbHashJoin(){
    //             cout << "\n" << "HashJoin::dummyDuckDbHashJoin";
    //             return true;
    //         }

    //         void preOp() override {
    //             BaseMergeAndJoinOp<KVSlice>::preOp();
    //             Iterator<KVSlice> *outer_iter = this->outer_->iterator();
    //             while (outer_iter->valid()) {
    //             KVSlice kv = outer_iter->key();
    //             std::string key(kv.data(), kv.key_size_bytes());
    //             if (outer_hash_map.find(key) == outer_hash_map.end()) {
    //                 outer_hash_map[key] = 0;
    //             }
    //             outer_hash_map[key]++;
    //             outer_iter->next();
    //             }
    //         }

    //         void doOpOnPartition(Partition partition, TableOpResult<KVSlice> *result) override {
    //             uint64_t outer_start = partition.outer.first;
    //             uint64_t outer_end = partition.outer.second;
    //             uint64_t inner_start = partition.inner.first;
    //             uint64_t inner_end = partition.inner.second;

    //             auto outer_iterator = this->outer_->getSSTableForSubRange(outer_start, outer_end)->iterator();
    //             auto inner_iterator = this->inner_->getSSTableForSubRange(inner_start, inner_end)->iterator();
    //             auto result_builder = this->result_builder_->getBuilderForRange(inner_start + outer_start, inner_end + outer_end);

    //             std::string prev;
    //             while (inner_iterator->valid()) {
    //                 KVSlice kv = inner_iterator->key();
    //                 std::string const key(kv.data(), kv.key_size_bytes());
    //                 if (outer_hash_map.find(key) != outer_hash_map.end() && prev != key) {
    //                 int repeats = outer_hash_map.at(key);
    //                 for (int i = 0; i < repeats; i++)
    //                     result_builder->add(inner_iterator->key());
    //                 }
    //                 prev = key;
    //                 inner_iterator->next();
    //             }
    //             result->stats["inner_disk_fetch"] = inner_iterator->getDiskFetches();
    //             result->stats["outer_disk_fetch"] = outer_iterator->getDiskFetches();
    //             result->output_table = result_builder->build();
    //         }
    //     private:
    //         std::unordered_map<std::string, uint64_t> outer_hash_map;
    // };

}