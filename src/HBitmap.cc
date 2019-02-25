#include "HBitmap.h"
#include <utility>

namespace helpers {
    void swap(HBitmap& lhs, HBitmap& rhs) noexcept {
        std::swap(lhs.m_hBitmap, rhs.m_hBitmap);
    }

    HBitmap::HBitmap(HBITMAP hBitmap) noexcept
    : m_hBitmap(hBitmap)
    {
        // do nothing
    };

    // moving is OK
    HBitmap::HBitmap(HBitmap&& src) noexcept
    : m_hBitmap(src.m_hBitmap)
    {
        src.m_hBitmap = nullptr;
    }

    HBitmap& HBitmap::operator=(HBitmap&& src) noexcept {
        if (this != &src) {
            Delete();
            m_hBitmap = src.m_hBitmap;
            src.m_hBitmap = nullptr;
        }

        return *this;
    }

    HBitmap::~HBitmap() noexcept {
        Delete();
    }

    void HBitmap::Delete() noexcept {
        if (m_hBitmap != nullptr) {
            DeleteObject(m_hBitmap);
            m_hBitmap = nullptr;
        }
    }

    HBitmap::operator bool() const noexcept {
        return (m_hBitmap != nullptr);
    }

    HBitmap::operator HBITMAP() const noexcept {
        return m_hBitmap;
    }

    HBITMAP* HBitmap::p_hbitmap() noexcept {
        return &m_hBitmap;
    }

    const HBITMAP* HBitmap::p_hbitmap() const noexcept {
        return &m_hBitmap;
    }
}