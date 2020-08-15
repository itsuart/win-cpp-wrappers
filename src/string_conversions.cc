#include "string_conversions.h"
#include <Windows.h>
#include <cstddef>

namespace helpers {

    std::unique_ptr<char[]> to_utf8(const wchar_t* input) {
        std::unique_ptr<char[]> empty;

        const std::size_t requiredSize = ::WideCharToMultiByte(CP_UTF8, 0, input, -1, nullptr, 0, nullptr, nullptr);
        if (!requiredSize) return empty;

        std::unique_ptr<char[]> result(new char[requiredSize]);

        const std::size_t
            charsProcessed = ::WideCharToMultiByte(CP_UTF8, 0, input, -1, result.get(), requiredSize, nullptr, nullptr);
        if (!charsProcessed) return empty;

        return result;
    }

    // Converts null-terminated wide (utf16) string into null-terminated utf8-encoded string
    // In case of error, result contains nullptr. Call GetLastError() to get the error code.
    std::string to_string(const wchar_t* input) {
        const std::size_t requiredSize = ::WideCharToMultiByte(CP_UTF8, 0, input, -1, nullptr, 0, nullptr, nullptr);
        if (!requiredSize) {
            return {};
        }

        std::string result;
        result.resize(requiredSize);

        const std::size_t charsProcessed =
            ::WideCharToMultiByte(CP_UTF8, 0, input, -1, &result[0], requiredSize, nullptr, nullptr);
        if (!charsProcessed) {
            return {};
        }

        //remove the trailing \0 that got inserted because we used -1 as length parameter to the api call
        result.resize(result.size() - 1);

        return result;
    }

    std::string to_string(const std::wstring& input) {
        //todo: redo
        return to_string(input.c_str());
    }

    std::unique_ptr<wchar_t[]> to_wide(const char* input) {
        std::unique_ptr<wchar_t[]> empty;

        const std::size_t requiredSize = ::MultiByteToWideChar(CP_UTF8, 0, input, -1, nullptr, 0);
        if (!requiredSize) return empty;

        std::unique_ptr<wchar_t[]> result(new wchar_t[requiredSize]);

        const std::size_t charsProcessed = ::MultiByteToWideChar(CP_UTF8, 0, input, -1, result.get(), requiredSize);
        if (!charsProcessed) return empty;

        return result;
    }

    std::wstring to_wstring(const char* input) {
        std::wstring result;

        const std::size_t requiredSize = ::MultiByteToWideChar(CP_UTF8, 0, input, -1, nullptr, 0);
        if (!requiredSize) {
            return {};
        }

        result.resize(requiredSize);

        const std::size_t charsProcessed = ::MultiByteToWideChar(CP_UTF8, 0, input, -1, &result[0], requiredSize);
        if (!charsProcessed) {
            return {}; // error
        }

        //remove the trailing \0 that got inserted because we used -1 as length parameter to the api call
        result.resize(result.size() - 1);

        return result;
    }
}
