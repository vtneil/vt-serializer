#ifndef VT_SERIALIZER_MEMORY_BUFFER_H
#define VT_SERIALIZER_MEMORY_BUFFER_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "serializer_utility.h"

namespace vt {
    template<typename T>
    class memory_buffer {
    private:
        T *ptr_ = nullptr;
        size_t size_ = 0;
        uint8_t has_buffer_ = 0;

    public:
        constexpr memory_buffer()
                : ptr_{static_cast<T *>(malloc(sizeof(T)))}, size_{sizeof(T)}, has_buffer_{1} {}

        constexpr memory_buffer(const memory_buffer &) = default;

        memory_buffer(memory_buffer &&) noexcept = default;

        explicit memory_buffer(const T &data)
                : memory_buffer() { memcpy(ptr_, &data, sizeof(T)); }

        ~memory_buffer() { if (has_buffer_ && (ptr_ != nullptr)) free(ptr_); }

        T *ptr() { return ptr_; }

        T *ptr() const { return ptr_; }

        size_t size() const { return size_; }

        T &operator*() { return *ptr_; }

        T *operator->() { return ptr_; }

        uint8_t *byte_ptr() { return reinterpret_cast<uint8_t *>(ptr_); }
    };

    namespace detail {
        template<typename T>
        class dynamic_container {
        private:
            T *data_ = nullptr;
            size_t size_ = 0;

        public:
            dynamic_container() = delete;

            dynamic_container(const dynamic_container &other) : dynamic_container(other.size_) {
                for (size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
            }

            dynamic_container(dynamic_container &&) noexcept = delete;

            explicit dynamic_container(size_t n)
                    : data_{new T[n]()}, size_(n) {}

            ~dynamic_container() { delete[] data_; }

            T &operator[](size_t i) { return *(data_ + i); }

            T &operator[](size_t i) const { return *(data_ + i); }

            T *ptr() { return data_; }

            T *ptr() const { return data_; }

            size_t size() const { return size_; }

            T &operator*() { return *data_; }

            T *operator->() { return data_; }
        };
    }

    using byte_pool = vt::detail::dynamic_container<uint8_t>;
}

#endif //VT_SERIALIZER_MEMORY_BUFFER_H
