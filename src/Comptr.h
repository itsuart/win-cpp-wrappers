#ifndef HELPERS_COMPTR_H
#define HELPERS_COMPTR_H

namespace helpers {

    // RAII wrapper over COM pointer
    template<typename T>
    class Comptr final {
    public:
        // Type of the COM object.
        using ComType = T;

        // Initializes internal pointer to COM object with nullptr.
        constexpr Comptr() noexcept : m_ptr(nullptr) {}

        // Initializes internal poiner to COM object with passed ptr.
        // AddRef of IUnknown is NOT called.
        explicit constexpr Comptr(T* ptr) noexcept : m_ptr(ptr) {}

        // Safely releases the COM object
        ~Comptr() noexcept {
            SafeRelease();
        }

        Comptr(const Comptr<T>& other) noexcept {
            other.AddRef();
            m_ptr = other.m_ptr;
        }

        Comptr<T>& operator=(const Comptr<T>& other) noexcept {
            if (this == &other) return *this;

            other.AddRef();
            T* copy = other.m_ptr;

            SafeRelease();

            m_ptr = copy;
            return *this;
        }

        Comptr<T>& operator=(T* otherRaw) noexcept {
            if (m_ptr == otherRaw) return *this;

            SafeRelease();
            m_ptr = otherRaw;
            return *this;
        }

        // moving

        Comptr(Comptr<T>&& other) noexcept : m_ptr(other.m_ptr) {
            other.m_ptr = nullptr;
        }

        Comptr<T>& operator=(Comptr<T>&& other) noexcept {
            if (this == &other) return *this;

            T* moved = other.m_ptr;

            SafeRelease();

            other.m_ptr = nullptr;
            m_ptr = moved;

            return *this;
        }

        // Returns pointer to the underlying COM object
        T* operator->() const noexcept { return m_ptr; }

        using PtrToComType = T*;
        operator PtrToComType() const noexcept { return m_ptr; }

        // returns raw pointer to the ComType
        PtrToComType ptr() const noexcept { return m_ptr; }

        using PtrToPtrToComType = T**;
        explicit operator PtrToPtrToComType() noexcept { return &m_ptr; }

        // returns raw pointer to raw pointer to ComType
        PtrToPtrToComType p_ptr() noexcept { return &m_ptr; }

        // returns raw pointer to raw pointer to ComType, casted to void**
        void** void_pptr() noexcept { return reinterpret_cast<void**>(p_ptr()); }

        void AddRef() noexcept {
            if (m_ptr) {
                m_ptr->AddRef();
            }
        }

        void SafeRelease() noexcept {
            if (m_ptr) {
                m_ptr->Release();
                m_ptr = nullptr;
            }
        }

    private:
        T* m_ptr;
    };
}

#endif
