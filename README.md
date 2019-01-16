# win-cpp-wrappers
Useful copy-pasteable C++11 wrappers over Windows API types

# How to use
Just copy-paste what you need. Everything is selfcontained.

# List of stuff

* AutoClearPropVariant: a std::unique_ptr-like wrapper over PROPVARIANT
* AutoCoTaskMemFree: a std::unique_ptr-like with some helpers built-in
* Comptr: will do AddRef/Release on destruction/copy/move with some helping methods builtin
* ErrorMessage: small functions to get system-formatted error message from a error code from COM/WinAPI
