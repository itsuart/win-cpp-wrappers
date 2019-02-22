#include "ErrorMessage.h"

namespace helpers {
    std::unique_ptr<char, decltype(LocalFree)*> get_error_message_a(DWORD errorCode) noexcept {
        char* message = nullptr;
        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            nullptr, errorCode, 0, (char*)&message, 1, nullptr);
        return std::unique_ptr<char, decltype(LocalFree)*>(message, LocalFree);
    }

    std::unique_ptr<wchar_t, decltype(LocalFree)*> get_error_message_w(DWORD errorCode) noexcept {
        wchar_t* message = nullptr;
        FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            nullptr, errorCode, 0, (wchar_t*)&message, 1, nullptr);
        return std::unique_ptr<wchar_t, decltype(LocalFree)*>(message, LocalFree);
    }
}
