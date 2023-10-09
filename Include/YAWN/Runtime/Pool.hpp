#pragma once 

#include "OID.hpp"
#include "../Core/Array.hpp"

namespace YAWN {
    class Pool {
    public:
        static constexpr OID None = OID();

    public:
        OID Acquire();

        void Dispose(OID id);

        bool IsValid(OID id) const;

        int GetSize() const;

        const OID* GetData() const;

    private:
        Array<OID> mPool;
        OID mDisposed = None;
    };
}
