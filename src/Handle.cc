#include "Handle.h"

namespace helpers {
    const Handle::WrappedType Handle::s_invalidValue = nullptr;

    Handle::Handle()
    : m_resource(s_invalidValue)
    {}

    Handle::Handle(WrappedType resource)
    : m_resource(resource == INVALID_HANDLE_VALUE ? s_invalidValue : resource) //unfortunately there are two invalid values for HANDLEs
    {}

    Handle::~Handle(){
        Release();
    }

    void Handle::Release(){
        if (m_resource != s_invalidValue){
            ::CloseHandle(m_resource);
            m_resource = s_invalidValue;
        }
    }

    Handle::Handle(Handle&& other)
    : m_resource(other.m_resource)
    {
        other.Release();
    }

    Handle& Handle::operator=(Handle&& other){
        if (&other == this) return *this;
        Release();
        m_resource = other.m_resource;
        other.Release();
    }

    // returns true iff wrapped resource is valid
    Handle::operator bool() const {
        return ok();
    }

    // returns true iff wrapped resource is valid
    bool Handle::ok() const{
        return m_resource != s_invalidValue;
    }

    Handle::operator WrappedType() const{
        return m_resource;
    }

    Handle::WrappedType Handle::Unwrap() const {
        return m_resource;
    }

    Handle::WrappedType* Handle::p_value(){
        return &m_resource;
    }

    const Handle::WrappedType* Handle::p_value() const{
        return &m_resource;
    }
}
