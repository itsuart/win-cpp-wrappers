#include "file_utils.h"
#include <Windows.h>

namespace helpers {
    // Returns size of "file" accessible by pFilePath
    // or -1 in case of error. Call GetLastError() for error details
    std::int64_t get_file_size(const wchar_t* pFilePath){
        HANDLE handle = ::CreateFileW(
            pFilePath,
            GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
            );
        if (handle == INVALID_HANDLE_VALUE) return -1;

        LARGE_INTEGER size;
        if (!::GetFileSizeEx(handle, &size)) {
            ::CloseHandle(handle);
            return -1;
        }
        ::CloseHandle(handle);

        return size.QuadPart;
    }
}
