#pragma once
#include <Windows.h>

namespace helpers {
    class AutoUnmappedViewOfFile final {
    public:
        using WrappedType = void*;

        AutoUnmappedViewOfFile();

        explicit AutoUnmappedViewOfFile(WrappedType resource);
        ~AutoUnmappedViewOfFile();

        // Resource types can not be copied

        AutoUnmappedViewOfFile(const AutoUnmappedViewOfFile&) = delete;
        AutoUnmappedViewOfFile& operator=(const AutoUnmappedViewOfFile&) = delete;

        // But can be moved

        AutoUnmappedViewOfFile(AutoUnmappedViewOfFile&& other);
        AutoUnmappedViewOfFile& operator=(AutoUnmappedViewOfFile&& other);

        // returns true iff wrapped resource is valid
        explicit operator bool() const;

        // returns true iff wrapped resource is valid
        bool ok() const;

        operator WrappedType() const;

        WrappedType unwrap() const;

        // Force releasing the resource
        void Release();

        WrappedType* p_value();

        const WrappedType* p_value() const;

        static const WrappedType s_invalidValue;

    private:
        WrappedType m_resource;
    };
}
