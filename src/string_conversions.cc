#include "string_conversions.h"
#include <Windows.h>
#include <cstddef>

namespace helpers {
    std::unique_ptr<char[]> to_utf8(const wchar_t* input) {
        std::unique_ptr<char[]> empty;

        const std::size_t requiredSize = WideCharToMultiByte(CP_UTF8, 0, input, -1, nullptr, 0, nullptr, nullptr);
        if (!requiredSize) return empty;

        std::unique_ptr<char[]> result(new char[requiredSize]);

        const std::size_t
            charsProcessed = WideCharToMultiByte(CP_UTF8, 0, input, -1, result.get(), requiredSize, nullptr, nullptr);
        if (!charsProcessed) return empty;

        return result;
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
            return result;
        }

        result.resize(requiredSize);

        const std::size_t charsProcessed = ::MultiByteToWideChar(CP_UTF8, 0, input, -1, &result[0], requiredSize);
        if (!charsProcessed) {
            result.resize(0); // error
        }

        return result;
    }
}
