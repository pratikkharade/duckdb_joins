//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/learned_join/interfaces/comparator.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

namespace learned_index {

    template <class T> class Comparator {
        public:
            virtual int compare(const T &first_key, const T &sec_key) = 0;
    };

    template <class T> class CountingComparator : public Comparator<T> {
        public:
            CountingComparator(Comparator<T> *comparator) : comparator_(comparator), comp_count_(0) {}
            int compare(const T &first_key, const T &sec_key) override {
                comp_count_++;
                return comparator_->compare(first_key, sec_key);
            }   
            uint64_t getCount() { return comp_count_; }

        private:
            Comparator<T> *comparator_;
            uint64_t comp_count_;
    };
}
