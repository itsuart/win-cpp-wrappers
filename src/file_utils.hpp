#ifndef HELPERS_FILE_UTILS_HPP
#define HELPERS_FILE_UTILS_HPP

#include <cstdint>

namespace helpers {
    // Returns size of "file" accessible by pFilePath
    // or -1 in case of error. Call GetLastError() for error details
    std::int64_t get_file_size(const wchar_t* pFilePath);
}

#endif
