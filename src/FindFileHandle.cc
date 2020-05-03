#include "FindFileHandle.h"

namespace helpers {

    const FindFileHandle::WrappedType FindFileHandle::s_invalidValue = INVALID_HANDLE_VALUE;

    FindFileHandle::FindFileHandle()
    : m_resource(s_invalidValue)
    {}

    FindFileHandle::FindFileHandle(WrappedType resource)
    : m_resource(resource)
    {}

    FindFileHandle::~FindFileHandle(){
        release();
    }

    void FindFileHandle::release(){
        if (m_resource != s_invalidValue){
            ::FindClose(m_resource);
            m_resource = s_invalidValue;
        }
    }

    FindFileHandle::FindFileHandle(FindFileHandle&& other)  noexcept
    : m_resource(other.m_resource)
    {
        other.m_resource = s_invalidValue;
    }

    FindFileHandle& FindFileHandle::operator=(FindFileHandle&& other) noexcept {
        if (&other != this){
            release();
            m_resource = other.m_resource;
            other.m_resource = s_invalidValue;
        }

        return *this;
    }

    // returns true iff wrapped resource is valid
    FindFileHandle::operator bool() const {
        return ok();
    }

    // returns true iff wrapped resource is valid
    bool FindFileHandle::ok() const{
        return m_resource != s_invalidValue;
    }

    FindFileHandle::operator WrappedType() const{
        return m_resource;
    }

    FindFileHandle::WrappedType FindFileHandle::unwrap() const {
        return m_resource;
    }

    FindFileHandle::WrappedType* FindFileHandle::p_value(){
        return &m_resource;
    }

    const FindFileHandle::WrappedType* FindFileHandle::p_value() const{
        return &m_resource;
    }

} // namespace
