//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/learned_join/algos/base_merge_and_join_op.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/execution/operator/learned_join/interfaces/comparator.hpp"
#include "duckdb/execution/operator/learned_join/interfaces/index.hpp"
#include "duckdb/execution/operator/learned_join/interfaces/iterator.hpp"
#include "duckdb/execution/operator/learned_join/algos/partition.hpp"
#include "duckdb/execution/operator/learned_join/interfaces/sstable.hpp"
#include "duckdb/execution/operator/learned_join/algos/table_op.hpp"


using namespace learned_index;

namespace learned_index {

    template <class T> class BaseMergeAndJoinOp: public TableOp<T> {
        public:
            BaseMergeAndJoinOp(
                SSTable<T> *outer, 
                SSTable<T> *inner, 
                IndexBuilder<T> *inner_index_builder,
                Comparator<T> *comparator,
                SSTableBuilder<uint64_t> *result_builder,
                int num_threads):
            TableOp<T>(outer, inner, result_builder, num_threads),
            comparator_(comparator),
            inner_index_builder_(inner_index_builder) {}

            void preOp() override {
                // Build Inner Index. You will always need this to partition.
                Iterator<T> inner_iter(*this->inner_);//->iterator();
                auto inner_index_build_begin = std::chrono::high_resolution_clock::now();
                while (inner_iter.valid()) {
                    inner_index_builder_->add(inner_iter.key());
                    inner_iter.next();
                }
                inner_index_ = this->inner_index_builder_->build();
                auto inner_index_build_end = std::chrono::high_resolution_clock::now();
                auto inner_index_build_duration_ns =
                    std::chrono::duration_cast<std::chrono::nanoseconds>(
                        inner_index_build_end - inner_index_build_begin).count();
                this->stats_["inner_index_build_duration_ns"] = inner_index_build_duration_ns;
                this->stats_["inner_index_size"] = inner_index_->sizeInBytes();
            }

            std::vector<Partition> getPartitions() override {
                return partition_sstables(this->num_threads_, *this->outer_, *this->inner_,
                                                inner_index_, comparator_);
            }

            void mergePartitions() override {
                uint64_t inner_disk_fetch_count = 0;
                uint64_t outer_disk_fetch_count = 0;
                for (int i = 0; i < this->num_threads_; i++) {
                    inner_disk_fetch_count += 1;
                    // (uint64_t)(this->partition_results_[i].stats["inner_disk_fetch"]);
                    outer_disk_fetch_count += 1;
                    // (uint64_t)(this->partition_results_[i].stats["outer_disk_fetch"]);
                }
                this->stats_["inner_disk_fetch"] = inner_disk_fetch_count;
                this->stats_["outer_disk_fetch"] = outer_disk_fetch_count;
                this->output_table_ = this->result_builder_->build();
            }
        protected:
            IndexBuilder<T> *inner_index_builder_;
            Index<T> *inner_index_;
            Comparator<T> *comparator_;
    };
}