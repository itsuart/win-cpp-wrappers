#ifndef HELPERS_AUTOCOTASKMEMFREE_H
#define HELPERS_AUTOCOTASKMEMFREE_H

#include <Objbase.h>

namespace helpers {

    template<typename T>
    class AutoCoTaskMemFree final {
    public:
        using MemType = T;

        explicit constexpr AutoCoTaskMemFree(T* ptr = nullptr) noexcept : m_ptr(ptr) {}

        ~AutoCoTaskMemFree() noexcept {
            SafeRelease();
        }

        // copying not allowed

        AutoCoTaskMemFree(const AutoCoTaskMemFree<T>&) = delete;
        AutoCoTaskMemFree<T> operator=(const AutoCoTaskMemFree<T>&) = delete;

        // moving

        AutoCoTaskMemFree(AutoCoTaskMemFree<T>&& other) noexcept : m_ptr(other.m_ptr) {
            other.m_ptr = nullptr;
        }

        AutoCoTaskMemFree<T>& operator=(AutoCoTaskMemFree<T>&& other) noexcept {
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

        // returns raw pointer to raw pointer to ComType
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
