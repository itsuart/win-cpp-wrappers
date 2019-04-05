#include "HBrush.h"

namespace helpers {
    const HBrush::WrappedType HBrush::s_invalidValue = nullptr;

    HBrush::HBrush()
    : m_resource(s_invalidValue)
    {}

    HBrush::HBrush(WrappedType resource)
    : m_resource(resource)
    {}

    HBrush::~HBrush(){
        release();
    }

    void HBrush::release(){
        if (m_resource != s_invalidValue){
            ::DeleteObject(m_resource);
            m_resource = s_invalidValue;
        }
    }

    HBrush::HBrush(HBrush&& other)
    : m_resource(other.m_resource)
    {
        other.m_resource = s_invalidValue;
    }

    HBrush& HBrush::operator=(HBrush&& other){
        if (&other != this){
            release();
            m_resource = other.m_resource;
            other.m_resource = s_invalidValue;
        }

        return *this;
    }

    // returns true iff wrapped resource is valid
    HBrush::operator bool() const {
        return ok();
    }

    // returns true iff wrapped resource is valid
    bool HBrush::ok() const{
        return m_resource != s_invalidValue;
    }

    HBrush::operator WrappedType() const{
        return m_resource;
    }

    HBrush::WrappedType HBrush::unwrap() const {
        return m_resource;
    }

    HBrush::WrappedType* HBrush::p_value(){
        return &m_resource;
    }

    const HBrush::WrappedType* HBrush::p_value() const{
        return &m_resource;
    }
}
