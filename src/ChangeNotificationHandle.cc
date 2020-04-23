#include "ChangeNotificationHandle.h"

namespace helpers {
    const ChangeNotificationHandle::WrappedType ChangeNotificationHandle::s_invalidValue = nullptr;

    ChangeNotificationHandle::ChangeNotificationHandle(
        const wchar_t* directory,
        bool watchSubtree,
        DWORD notificationFilter
    )
        : m_resource(::FindFirstChangeNotificationW(directory, watchSubtree, notificationFilter))
    {}

    ChangeNotificationHandle::ChangeNotificationHandle(
        const char* directory,
        bool watchSubtree,
        DWORD notificationFilter
    )
        : m_resource(::FindFirstChangeNotificationA(directory, watchSubtree, notificationFilter))
    {}


    ChangeNotificationHandle::~ChangeNotificationHandle(){
        release();
    }

    void ChangeNotificationHandle::release(){
        if (m_resource != s_invalidValue){
            ::FindCloseChangeNotification(m_resource);
            m_resource = s_invalidValue;
        }
    }

    ChangeNotificationHandle::ChangeNotificationHandle(ChangeNotificationHandle&& other) noexcept
    : m_resource(other.m_resource)
    {
        other.m_resource = s_invalidValue;
    }

    ChangeNotificationHandle& ChangeNotificationHandle::operator=(ChangeNotificationHandle&& other) noexcept {
        if (&other != this){
            release();
            m_resource = other.m_resource;
            other.m_resource = s_invalidValue;
        }

        return *this;
    }

    // Starts infinite wait for the changes.
    // Returns result of ::WaitForSingleObject
    DWORD ChangeNotificationHandle::wait_for_changes() const {
        return wait_for_changes(INFINITE);
    }

    // Starts wait for the changes for specified number of milliseconds.
    DWORD ChangeNotificationHandle::wait_for_changes(DWORD dwMillis) const {
        if (::FindNextChangeNotification(m_resource)) {
            return ::WaitForSingleObject(m_resource, dwMillis);
        }
        else {
            return WAIT_FAILED;
        }
    }

    // Starts infinite wait for the changes or hWakeupEvent signalled state.
    // Returns result of ::WaitForMultipleObjects(notificationHandle, hWakeupEvent)
    DWORD ChangeNotificationHandle::wait_for_changes(HANDLE hCancelWaitEvent) const {
        return wait_for_changes(hCancelWaitEvent, INFINITE);
    }

    // Starts wait for the changes for specified number of milliseconds.
    DWORD ChangeNotificationHandle::wait_for_changes(HANDLE hCancelWaitEvent, DWORD dwMillis) const {
        if (::FindNextChangeNotification(m_resource)) {
            const HANDLE waitHandles[] = { m_resource, hCancelWaitEvent };
            return ::WaitForMultipleObjects(2, &waitHandles[0], false, dwMillis);
        }
        else {
            return WAIT_FAILED;
        }
    }

} // namespace
