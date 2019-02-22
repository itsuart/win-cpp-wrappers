#ifndef HELPERS_ERRORMESSAGE_H
#define HELPERS_ERRORMESSAGE_H

#include <memory>
#include <Windows.h>

namespace helpers {
    std::unique_ptr<char, decltype(LocalFree)*> get_error_message_a(DWORD errorCode) noexcept;
    std::unique_ptr<wchar_t, decltype(LocalFree)*> get_error_message_w(DWORD errorCode) noexcept;
}

#endif
