//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/operator/learned_join/sstable/key_value_slice.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

namespace learned_index {

    class KVSlice {
    public:
        KVSlice() : data_(nullptr), key_size_bytes_(0), value_size_bytes_(0) {}
        KVSlice(const char *data, int key_size_bytes, int value_size_bytes)
            : data_(data), key_size_bytes_(key_size_bytes), value_size_bytes_(value_size_bytes) {}
        int key_size_bytes() const { return key_size_bytes_; }
        int value_size_bytes() const { return value_size_bytes_; }
        int total_size_bytes() const { return key_size_bytes_ + value_size_bytes_; }
        const char *data() const { return data_; }

        static KVSlice copy_kvslice(char *copy_buf, const KVSlice &kv) {
            memcpy(copy_buf, kv.data(), kv.total_size_bytes());
            return KVSlice(copy_buf, kv.key_size_bytes(), kv.value_size_bytes());
        }
        void dump_kv() const {
            for (int i = 0; i < key_size_bytes_ + value_size_bytes_; i++) {
                printf("%02x ", *(unsigned char *)(data_ + i));
            }
            printf("\n");
        }

    private:
        int key_size_bytes_;
        int value_size_bytes_;
        const char *data_;
};
}


