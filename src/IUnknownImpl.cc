#include "IUnknownImpl.h"

namespace helpers {
    IUnknownImpl::IUnknownImpl() noexcept : m_refs(1) {}

    ULONG __stdcall IUnknownImpl::AddRef() {
        return InterlockedIncrement(&m_refs);
    }

    ULONG __stdcall IUnknownImpl::Release() {
        ULONG result = InterlockedDecrement(&m_refs);
        if (result == 0) {
            delete this;
        }

        return result;
    }

    HRESULT __stdcall IUnknownImpl::QueryInterface(const IID& requestedIID, void** ppv) {
        if (ppv == nullptr) {
            return E_POINTER;
        }

        if (!::IsEqualGUID(requestedIID, IID_IUnknown)) {
            *ppv = 0;
            return E_NOINTERFACE;
        }

        *ppv = this;
        AddRef();
        return S_OK;
    }
}
