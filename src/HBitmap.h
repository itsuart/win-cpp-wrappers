#pragma once
#include <Windows.h>

namespace helpers {
    // thin RAII wrapper over HBITMAP, calls DeleteObject on destruction
    class HBitmap final {
        friend void swap(HBitmap& lhs, HBitmap& rhs) noexcept;

    public:
        explicit HBitmap(HBITMAP hHBitmap = nullptr) noexcept;

        // as any other resource, bitmaps can't be copy-asssigned and copy-constructed
        HBitmap(const HBitmap& src) = delete;
        HBitmap& operator=(const HBitmap& src) = delete;

        // moving is OK
        HBitmap(HBitmap&& src) noexcept;
        HBitmap& operator=(HBitmap&& src) noexcept;

        ~HBitmap() noexcept;

        // deletes underlying HBITMAP
        void Delete() noexcept;

        // true if object contains non-null HBITMAP
        explicit operator bool() const noexcept;

        operator HBITMAP() const noexcept;

        HBITMAP* p_hbitmap() noexcept;

        const HBITMAP* p_hbitmap() const noexcept;

    private:
        HBITMAP m_hBitmap;
    };
}