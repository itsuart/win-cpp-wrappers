#include "AutoUnmappedViewOfFile.h"

namespace helpers {
    const AutoUnmappedViewOfFile::WrappedType AutoUnmappedViewOfFile::s_invalidValue = nullptr;

    AutoUnmappedViewOfFile::AutoUnmappedViewOfFile()
    : m_resource(s_invalidValue)
    {}

    AutoUnmappedViewOfFile::AutoUnmappedViewOfFile(WrappedType resource)
    : m_resource(resource)
    {}

    AutoUnmappedViewOfFile::~AutoUnmappedViewOfFile(){
        Release();
    }

    void AutoUnmappedViewOfFile::Release(){
        if (m_resource != s_invalidValue){
            ::UnmapViewOfFile(m_resource);
            m_resource = s_invalidValue;
        }
    }

    AutoUnmappedViewOfFile::AutoUnmappedViewOfFile(AutoUnmappedViewOfFile&& other)
    : m_resource(other.m_resource)
    {
        other.m_resource = s_invalidValue;
    }

    AutoUnmappedViewOfFile& AutoUnmappedViewOfFile::operator=(AutoUnmappedViewOfFile&& other){
        if (&other != this){
            Release();
            m_resource = other.m_resource;
            other.m_resource = s_invalidValue;
        }

        return *this;
    }

    // returns true iff wrapped resource is valid
    AutoUnmappedViewOfFile::operator bool() const {
        return ok();
    }

    // returns true iff wrapped resource is valid
    bool AutoUnmappedViewOfFile::ok() const{
        return m_resource != s_invalidValue;
    }

    AutoUnmappedViewOfFile::operator WrappedType() const{
        return m_resource;
    }

    AutoUnmappedViewOfFile::WrappedType AutoUnmappedViewOfFile::unwrap() const {
        return m_resource;
    }

    AutoUnmappedViewOfFile::WrappedType* AutoUnmappedViewOfFile::p_value(){
        return &m_resource;
    }

    const AutoUnmappedViewOfFile::WrappedType* AutoUnmappedViewOfFile::p_value() const{
        return &m_resource;
    }
}
