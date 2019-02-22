#ifndef HELPERS_STRING_CONVERSIONS_H
#define HELPERS_STRING_CONVERSIONS_H

#include <memory>
#include <type_traits>

namespace helpers {
    // Converts null-terminated wide (utf16) string into null-terminated utf8-encoded string
    // In case of error, result constains nullptr. Call GetLastError() to get the error code.
    std::unique_ptr<char[]> to_utf8(const wchar_t* input);

    // Converts null-terminated utf8-encoded string into null-terminated wide string (utf16)
    // In case of error, result constains nullptr. Call GetLastError() to get the error code.
    std::unique_ptr<wchar_t[]> to_wide(const char* input);

    // Converts null-terminated utf8-encoded string into null-terminated wide string (utf16)
    // In case of error, result constains nullptr. Call GetLastError() to get the error code.
    template<typename T, class = std::enable_if<sizeof(T) == 1>::type>
    std::unique_ptr<wchar_t[]> to_wide(const T* input) {
        return to_wide(reinterpret_cast<const char*>(input));
    }

}

#endif
