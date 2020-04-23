#pragma once
#include <Windows.h>

namespace helpers {

    /*
        Wrapper over HANDLE that FindFirstNotification, FindNextNotification, etc WINAPI functions use.
        Will call FindCloseNotification in destructor.
    */
    class ChangeNotificationHandle final {
    public:
        using WrappedType = HANDLE;

        // Wraps over s_invalidValue
        ChangeNotificationHandle() : m_resource(s_invalidValue){}

        explicit ChangeNotificationHandle(WrappedType resource) : m_resource(resource) {}

        ChangeNotificationHandle(const wchar_t* directory, bool watchSubtree, DWORD notificationFilter);

        ChangeNotificationHandle(const char* directory, bool watchSubtree, DWORD notificationFilter);

        ~ChangeNotificationHandle();

        // Resource types can not be copied

        ChangeNotificationHandle(const ChangeNotificationHandle&) = delete;
        ChangeNotificationHandle& operator=(const ChangeNotificationHandle&) = delete;

        // But can be moved

        ChangeNotificationHandle(ChangeNotificationHandle&& other) noexcept;
        ChangeNotificationHandle& operator=(ChangeNotificationHandle&& other) noexcept;

        // Starts infinite wait for the changes.
        // Returns result of ::WaitForSingleObject
        DWORD wait_for_changes() const;

        // Starts wait for the changes for specified number of milliseconds.
        DWORD wait_for_changes(DWORD dwMillis) const;

        // Starts infinite wait for the changes or hWakeupEvent signalled state.
        // Returns result of ::WaitForMultipleObjects(notificationHandle, hCancelWaitEvent)
        DWORD wait_for_changes(HANDLE hCancelWaitEvent) const;

        // Starts wait for the changes for specified number of milliseconds.
        DWORD wait_for_changes(HANDLE hCancelWaitEvent, DWORD dwMillis) const;

        // returns true iff wrapped resource is valid
        explicit operator bool() const {
            return ok();
        }

        // returns true iff wrapped resource is valid
        bool ok() const {
            return m_resource != ChangeNotificationHandle::s_invalidValue;
        }

        operator WrappedType() const {
            return m_resource;
        }

        WrappedType unwrap() const {
            return m_resource;
        }

        // Force release the resource
        void release();

        WrappedType* p_value() {
            return &m_resource;
        }

        const WrappedType* p_value() const {
            return &m_resource;
        }


        static const WrappedType s_invalidValue;

    private:
        WrappedType m_resource;
    };

    enum class NotificationFilter : DWORD {
        FileName = FILE_NOTIFY_CHANGE_FILE_NAME,
        DirectoryName = FILE_NOTIFY_CHANGE_DIR_NAME,
        Attributes = FILE_NOTIFY_CHANGE_ATTRIBUTES,
        Size = FILE_NOTIFY_CHANGE_SIZE,
        LastWrite = FILE_NOTIFY_CHANGE_LAST_WRITE,
        Security = FILE_NOTIFY_CHANGE_SECURITY
    };

    inline DWORD operator| (const DWORD lhs, NotificationFilter rhs) {
        return lhs | static_cast<DWORD>(rhs);
    }

    inline DWORD operator| (NotificationFilter lhs, NotificationFilter rhs) {
        return static_cast<DWORD>(lhs) | static_cast<DWORD>(rhs);
    }

} // namespace
