#pragma once

#include <windows.h>

namespace helpers {
    // thin RAII wrapper over HDCs that should be DeleteDC'ed when no longer needed.
    class DeletableDc {
        friend void swap(DeletableDc& lhs, DeletableDc& rhs) noexcept;

    public:
        DeletableDc(HDC hdc = nullptr) noexcept;
        ~DeletableDc() noexcept;

        // DC can't be copied
        DeletableDc(const DeletableDc& src) = delete;
        DeletableDc& operator = (const DeletableDc& other) = delete;

        // But can be moved
        DeletableDc(DeletableDc&& src) noexcept;
        DeletableDc& operator=(DeletableDc&& src) noexcept;

        void Delete() noexcept;

        HDC Unwrap() const noexcept;

        explicit operator bool() const noexcept;

        operator HDC() const noexcept;

        // returns pointer to the stored HDC value
        HDC* p_hdc() noexcept;

    private:
        HDC m_hdc;
    };
}