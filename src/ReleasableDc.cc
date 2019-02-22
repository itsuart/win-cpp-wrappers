#pragma comment(lib, "gdi32.lib")

#include "ReleasableDc.h"

#include <utility>


namespace helpers {
    void swap(ReleasableDc& lhs, ReleasableDc& rhs) noexcept {
        std::swap(lhs.m_hdc, rhs.m_hdc);
        std::swap(lhs.m_hwnd, rhs.m_hwnd);
    }

    ReleasableDc::ReleasableDc(HDC hdc, HWND hwnd) noexcept
    : m_hdc(hdc), m_hwnd(hwnd)
    {}

    ReleasableDc::~ReleasableDc() noexcept {
        Release();
    }

    ReleasableDc::ReleasableDc(ReleasableDc&& src) noexcept
    : m_hwnd(src.m_hwnd), m_hdc(src.m_hdc)
    {
        src.m_hwnd = nullptr;
        src.m_hdc = nullptr;
    }

    ReleasableDc& ReleasableDc::operator=(ReleasableDc&& src) noexcept {
        if (&src != this) {
            Release();

            m_hdc = src.m_hdc;
            m_hwnd = src.m_hwnd;

            src.m_hdc = nullptr;
            src.m_hwnd = nullptr;
        }

        return *this;
    }

    void ReleasableDc::Release() noexcept {
        ::ReleaseDC(m_hwnd, m_hdc);
        m_hdc = nullptr;
        m_hwnd = nullptr;
    }

    HDC ReleasableDc::Unwrap() const noexcept {
        return m_hdc;
    }

    ReleasableDc::operator bool() const noexcept {
        return m_hdc != nullptr;
    }

    ReleasableDc::operator HDC() const noexcept {
        return Unwrap();
    }

    HDC* ReleasableDc::p_hdc() noexcept {
        return &m_hdc;
    }
}