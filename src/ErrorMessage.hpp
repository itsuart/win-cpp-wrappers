#ifndef HELPERS_ERRORMESSAGE_HPP
#define HELPERS_ERRORMESSAGE_HPP

#include <memory>
#include <Windows.h>

namespace helpers {
    std::unique_ptr<char, decltype(LocalFree)*> get_error_messsage_a(DWORD errorCode) noexcept;
    std::unique_ptr<wchar_t, decltype(LocalFree)*> get_error_messsage_w(DWORD errorCode) noexcept;
}

#endif