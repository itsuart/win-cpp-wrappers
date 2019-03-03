#pragma once
#include <unknwn.h>

namespace helpers {
    class IUnknownImpl : public IUnknown {
    public:
        IUnknownImpl() noexcept;

        virtual ~IUnknownImpl() {};

        virtual ULONG __stdcall AddRef() override;

        virtual ULONG __stdcall Release() override;

        virtual HRESULT __stdcall QueryInterface(const IID& requestedIID, void** ppv) override;

    protected:
        ULONG m_refs;
    };
}
