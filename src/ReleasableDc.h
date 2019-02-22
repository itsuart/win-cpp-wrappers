#pragma once

#include <windows.h>

namespace helpers {
    class ReleasableDc final {
        friend void swap(ReleasableDc& lhs, ReleasableDc& rhs) noexcept;

    public:
        ReleasableDc(HDC hdc = nullptr, HWND hwnd = nullptr) noexcept;

        ~ReleasableDc() noexcept;

        // DC can't be copied
        ReleasableDc(const ReleasableDc& src) = delete;
        ReleasableDc& operator = (const ReleasableDc& other) = delete;

        // But can be moved
        ReleasableDc(ReleasableDc&& src) noexcept;
        ReleasableDc& operator=(ReleasableDc&& src) noexcept;

        void Release() noexcept;

        HDC Unwrap() const noexcept;

        explicit operator bool() const noexcept;

        operator HDC() const noexcept;

        // returns pointer to the stored HDC value
        HDC* p_hdc() noexcept;

    private:
        HWND m_hwnd; //could be nullptr (for Desktop's DC)
        HDC m_hdc;
    };
}
