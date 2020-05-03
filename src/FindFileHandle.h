#pragma once
#include <Windows.h>

namespace helpers {

    class FindFileHandle final {
    public:
        using WrappedType = HANDLE;

        // Wraps over s_invalidValue
        FindFileHandle();

        explicit FindFileHandle(WrappedType resource);
        ~FindFileHandle();

        // Resource types can not be copied

        FindFileHandle(const FindFileHandle&) = delete;
        FindFileHandle& operator=(const FindFileHandle&) = delete;

        // But can be moved

        FindFileHandle(FindFileHandle&& other) noexcept ;
        FindFileHandle& operator=(FindFileHandle&& other) noexcept ;

        // returns true iff wrapped resource is valid
        explicit operator bool() const;

        // returns true iff wrapped resource is valid
        bool ok() const;

        operator WrappedType() const;

        WrappedType unwrap() const;

        // Force release the resource
        void release();

        WrappedType* p_value();

        const WrappedType* p_value() const;

        static const WrappedType s_invalidValue;

    private:
        WrappedType m_resource;
    };

} // namespace
