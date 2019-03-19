#pragma once
#include <Windows.h>

namespace helpers {
    class Handle final {
    public:
        using WrappedType = ::HANDLE;

        Handle();

        explicit Handle(WrappedType resource);
        ~Handle();

        // Resource types can not be copied

        Handle(const Handle&) = delete;
        Handle& operator=(const Handle&) = delete;

        // But can be moved

        Handle(Handle&& other);
        Handle& operator=(Handle&& other);

        // returns true iff wrapped resource is valid
        explicit operator bool() const;

        // returns true iff wrapped resource is valid
        bool ok() const;

        operator WrappedType() const;

        WrappedType Unwrap() const;

        // Force release the resource
        void Release();

        WrappedType* p_value();

        const WrappedType* p_value() const;

        static const WrappedType s_invalidValue;

    private:
        WrappedType m_resource;
    };
}
