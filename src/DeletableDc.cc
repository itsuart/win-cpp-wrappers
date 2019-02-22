#pragma comment(lib, "gdi32.lib")

#include "DeletableDc.h"

#include <utility>


namespace helpers {
    void swap(DeletableDc& lhs, DeletableDc& rhs) noexcept {
        std::swap(lhs.m_hdc, rhs.m_hdc);
    }

    DeletableDc::DeletableDc(HDC hdc) noexcept
    : m_hdc(hdc)
    {}

    DeletableDc::~DeletableDc() noexcept {
        Delete();
    }

    DeletableDc::DeletableDc(DeletableDc&& src) noexcept
        : m_hdc(src.m_hdc) {
        src.m_hdc = nullptr;
    }

    DeletableDc& DeletableDc::operator=(DeletableDc&& src) noexcept {
        if (&src != this) {
            Delete();
            m_hdc = src.m_hdc;
            src.m_hdc = nullptr;
        }

        return *this;
    }

    void DeletableDc::Delete() noexcept {
        if (m_hdc) {
            ::DeleteDC(m_hdc);
            m_hdc = nullptr;
        }
    }

    HDC DeletableDc::Unwrap() const noexcept {
        return m_hdc;
    }

    DeletableDc::operator bool() const noexcept {
        return m_hdc != nullptr;
    }

    DeletableDc::operator HDC() const noexcept {
        return Unwrap();
    }

    HDC* DeletableDc::p_hdc() noexcept {
        return &m_hdc;
    }
}