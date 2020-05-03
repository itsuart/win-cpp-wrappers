#pragma once
#include <Windows.h>

namespace helpers {

    class IoCompletionPort final {
    public:
        using WrappedType = HANDLE;

        // Wraps over s_invalidValue
        IoCompletionPort();

        explicit IoCompletionPort(WrappedType resource);

        explicit IoCompletionPort(DWORD dwNumberOfConcurrentThreads);

        ~IoCompletionPort();

        // Resource types can not be copied

        IoCompletionPort(const IoCompletionPort&) = delete;
        IoCompletionPort& operator=(const IoCompletionPort&) = delete;

        // But can be moved

        IoCompletionPort(IoCompletionPort&& other);
        IoCompletionPort& operator=(IoCompletionPort&& other);

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

        //Useful, but short and simple helping wrappers over related WinAPI.

        // associates passed device handle with the completion port
        bool associate_device(HANDLE deviceHandle, ULONG_PTR completionKey);

        // Takes one completions status record or waits for it for dwMilliseconds.
        bool GetQueuedCompletionStatus(
            DWORD* nBytesTransferred,
            ULONG_PTR* pCompletionKey,
            LPOVERLAPPED* lpOverlapped,
            DWORD dwMilliseconds
        );

        bool PostQueuedCompletionStatus(
            DWORD dwNumberOfBytesTransferred,
            ULONG_PTR dwCompletionKey,
            LPOVERLAPPED lpOverlapped
        );

    private:
        WrappedType m_resource;
    };

} // namespace
