#pragma once
#include <cstdint>
#include <Windows.h>

namespace helpers {

    /* Thin wrapper over Windows' HRESULT value*/
    class HResult {
    public:
        constexpr HResult() : _value(E_FAIL) {}; // an unspecified error

        constexpr HResult(HRESULT value) : _value(value) {};
    
        constexpr operator HRESULT() const {
            return _value;
        }

        constexpr explicit operator bool() const {
            return ok();
        }

        constexpr bool ok() const {
            return 0 == (_value & 0x80000000);
        }

        constexpr bool failed() const {
            return 1 == (_value & 0x80000000);
        }

        HRESULT value() const {
            return _value;
        }

        HRESULT* ptr() {
            return &_value;
        }

        constexpr std::uint16_t facility() const {
            return (_value >> 16) & 0b0000'0111'1111'1111;
        }

        constexpr std::uint16_t code() const {
            return (std::uint16_t)(_value & 0xFF'FF);
        }

    private:
        HRESULT _value;
    };
} //namespace
