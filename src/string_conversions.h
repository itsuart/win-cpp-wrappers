#ifndef HELPERS_STRING_CONVERSIONS_H
#define HELPERS_STRING_CONVERSIONS_H

#include <memory>
#include <string>
#include <type_traits>
#include <string>

namespace helpers {
    // Converts null-terminated wide (utf16) string into null-terminated utf8-encoded string
    // In case of error, result contains nullptr. Call GetLastError() to get the error code.
    std::unique_ptr<char[]> to_utf8(const wchar_t* input);

    // Converts null-terminated wide (utf16) string into null-terminated utf8-encoded string
    // In case of error, result contains nullptr. Call GetLastError() to get the error code.
    std::string to_string(const wchar_t* input);

    // Converts null-terminated wide (utf16) string into null-terminated utf8-encoded string
    // In case of error, result contains nullptr. Call GetLastError() to get the error code.
    std::string to_string(const std::wstring& input);

    // Converts null-terminated utf8-encoded string into null-terminated wide string (utf16)
    // In case of error, result contains nullptr. Call GetLastError() to get the error code.
    std::unique_ptr<wchar_t[]> to_wide(const char* input);

    // Converts null-terminated utf8-encoded string into null-terminated wide string (utf16)
    // In case of error, result constains nullptr. Call GetLastError() to get the error code.
    template<typename T, class = typename std::enable_if<sizeof(T) == 1>::type>
    std::unique_ptr<wchar_t[]> to_wide(const T* input) {
        return to_wide(reinterpret_cast<const char*>(input));
    }

    // Converts null-terminated utf8-encoded string into null-terminated wide string (utf16)
    // In case of error, result is an empty string. Call GetLastError() to get the error code.
    std::wstring to_wstring(const char* input);

    inline std::wstring to_wstring(const std::string& utf8String) {
        return to_wstring(utf8String.c_str());
    }

    // Converts null-terminated utf8-encoded string into null-terminated wide string (utf16)
    // In case of error, result is an empty string. Call GetLastError() to get the error code.
    template<typename T, class = typename std::enable_if<sizeof(T) == 1>::type>
    std::wstring to_wstring(const T* input) {
        return to_wstring(reinterpret_cast<const char*>(input));
    }
}

#endif
