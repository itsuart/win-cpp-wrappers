#include "IoCompletionPort.h"
#include <cassert>

namespace helpers {

    const IoCompletionPort::WrappedType IoCompletionPort::s_invalidValue = nullptr;

    IoCompletionPort::IoCompletionPort()
    : m_resource(s_invalidValue)
    {}

    IoCompletionPort::IoCompletionPort(WrappedType resource)
    : m_resource(resource)
    {}

    IoCompletionPort::IoCompletionPort(DWORD dwNumberOfConcurrentThreads)
        : m_resource(::CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, dwNumberOfConcurrentThreads))
    {}

    IoCompletionPort::~IoCompletionPort(){
        release();
    }

    void IoCompletionPort::release(){
        if (m_resource != s_invalidValue){
            ::CloseHandle(m_resource);
            m_resource = s_invalidValue;
        }
    }

    IoCompletionPort::IoCompletionPort(IoCompletionPort&& other)
    : m_resource(other.m_resource)
    {
        other.m_resource = s_invalidValue;
    }

    IoCompletionPort& IoCompletionPort::operator=(IoCompletionPort&& other){
        if (&other != this){
            release();
            m_resource = other.m_resource;
            other.m_resource = s_invalidValue;
        }

        return *this;
    }

    // returns true iff wrapped resource is valid
    IoCompletionPort::operator bool() const {
        return ok();
    }

    // returns true iff wrapped resource is valid
    bool IoCompletionPort::ok() const{
        return m_resource != s_invalidValue;
    }

    IoCompletionPort::operator WrappedType() const{
        return m_resource;
    }

    IoCompletionPort::WrappedType IoCompletionPort::unwrap() const {
        return m_resource;
    }

    IoCompletionPort::WrappedType* IoCompletionPort::p_value(){
        return &m_resource;
    }

    const IoCompletionPort::WrappedType* IoCompletionPort::p_value() const{
        return &m_resource;
    }

    // associates passed device handle with the completion port
    bool IoCompletionPort::associate_device(HANDLE deviceHandle, ULONG_PTR completionKey) {
        assert(deviceHandle != nullptr and "deviceHanle is nullptr");
        assert(deviceHandle != INVALID_HANDLE_VALUE and "deviceHandle is INVALID_HANDLE_VALUE");

        const HANDLE result = ::CreateIoCompletionPort(deviceHandle, m_resource, completionKey, 0);
        return (result == m_resource);
    }

    bool IoCompletionPort::GetQueuedCompletionStatus(
        DWORD* nBytesTransferred,
        ULONG_PTR* pCompletionKey,
        LPOVERLAPPED* lpOverlapped,
        DWORD dwMilliseconds
    ) {
        return ::GetQueuedCompletionStatus(m_resource, nBytesTransferred, pCompletionKey, lpOverlapped, dwMilliseconds);
    }

    bool IoCompletionPort::PostQueuedCompletionStatus(
        DWORD dwNumberOfBytesTransferred,
        ULONG_PTR dwCompletionKey,
        LPOVERLAPPED lpOverlapped
    ) {
        return ::PostQueuedCompletionStatus(m_resource, dwNumberOfBytesTransferred, dwCompletionKey, lpOverlapped);
    }

} // namespace
