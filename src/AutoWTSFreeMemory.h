#ifndef HELPERS_AUTOWTSFREEMEMORY_H
#define HELPERS_AUTOWTSFREEMEMORY_H

#include <Objbase.h>

namespace helpers {

    template<typename T>
    class AutoWTSFreeMemory final {
    public:
        using MemType = T;

        explicit constexpr AutoWTSFreeMemory(T* ptr = nullptr) noexcept : m_ptr(ptr) {}

        ~AutoWTSFreeMemory() noexcept {
            SafeRelease();
        }

        // copying not allowed

        AutoWTSFreeMemory(const AutoWTSFreeMemory<T>&) = delete;
        AutoWTSFreeMemory<T> operator=(const AutoWTSFreeMemory<T>&) = delete;

        // moving

        AutoWTSFreeMemory(AutoWTSFreeMemory<T>&& other) noexcept : m_ptr(other.m_ptr) {
            other.m_ptr = nullptr;
        }

        AutoWTSFreeMemory<T>& operator=(AutoWTSFreeMemory<T>&& other) noexcept {
            if (this == &other) return *this;

            T* moved = other.m_ptr;

            SafeRelease();

            other.m_ptr = nullptr;
            m_ptr = moved;

            return *this;
        }

        T* operator->() const noexcept { return m_ptr; }

        using PtrToMemType = T*;
        operator PtrToMemType() const noexcept { return m_ptr; }

        // returns raw pointer to the MemType
        PtrToMemType ptr() const noexcept { return m_ptr; }

        using PtrToPtrToMemType = T**;
        explicit operator PtrToPtrToMemType() noexcept { return &m_ptr; }

        // returns raw pointer to raw pointer to MemType
        PtrToPtrToMemType p_ptr() noexcept { return &m_ptr; }

        void SafeRelease() noexcept {
            if (m_ptr) {
                CoTaskMemFree(m_ptr);
                m_ptr = nullptr;
            }
        }

    private:
        T* m_ptr;
    };
}

#endif
