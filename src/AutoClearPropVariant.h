#ifndef HELPERS_AUTOCLEARPROPVARIANT_H
#define HELPERS_AUTOCLEARPROPVARIANT_H

#include <Propidl.h>

namespace helpers{
    class AutoClearPropVariant final {
    public:
        using PPropVariant = PROPVARIANT*;

        explicit AutoClearPropVariant(const PROPVARIANT* val) noexcept {
            PropVariantCopy(&m_value, val);
        }

        AutoClearPropVariant() noexcept {
            PropVariantInit(&m_value);
        }

        // copying
        AutoClearPropVariant(const AutoClearPropVariant& other) noexcept {
            PropVariantCopy(&m_value, &other.m_value);
        }

        AutoClearPropVariant& operator=(const AutoClearPropVariant& other) noexcept {
            if (this == &other) return *this;

            PROPVARIANT copy;
            if (S_OK == PropVariantCopy(&copy, &other.m_value)){
                if (S_OK == PropVariantClear(&m_value)){
                    m_value = copy;
                }
            }

            return *this;
        }

        // moving
        AutoClearPropVariant(AutoClearPropVariant&& other) noexcept {
            if (S_OK == PropVariantCopy(&m_value, &other.m_value)){
                other.~AutoClearPropVariant();
            }
        }

        AutoClearPropVariant& operator=(AutoClearPropVariant&& other) noexcept {
            if (this == &other) return *this;

            PROPVARIANT copy;
            if (S_OK == PropVariantCopy(&copy, &other.m_value)){
                if (S_OK == PropVariantClear(&m_value)){
                    m_value = copy;
                    other.~AutoClearPropVariant();
                }
            }
            return *this;
        }

        operator PPropVariant() noexcept { return &m_value;}
        PROPVARIANT* ptr() noexcept { return &m_value;};

        PROPVARIANT* operator->() noexcept { return &m_value; };

        ~AutoClearPropVariant() noexcept{
            PropVariantClear(&m_value);
        }

    private:
        PROPVARIANT m_value;
    };
}

#endif
