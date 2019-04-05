#pragma once
#include <Windows.h>
namespace helpers {
    class HBrush final {
    public:
        using WrappedType = HBRUSH;

        // Wraps over s_invalidValue
        HBrush();

        explicit HBrush(WrappedType resource);
        ~HBrush();

        // Resource types can not be copied

        HBrush(const HBrush&) = delete;
        HBrush& operator=(const HBrush&) = delete;

        // But can be moved

        HBrush(HBrush&& other);
        HBrush& operator=(HBrush&& other);

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
}
