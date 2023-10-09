#pragma once 

#include "../Core/FNV1a.hpp"
#include "../Core/Config.hpp"
#include "../Core/TypeTraits.hpp"

namespace YAWN {
    namespace Internal {
        template<typename T>
        static constexpr int TypeHash() {
            return FNV1a::Hash(YAWN_PRETTY_FUNCTION);
        }
    }

    class TypeId {
    public:
        template<typename T>
        static constexpr TypeId From() {
#if 1       // Get TypeId compatible across boundaries.
            return TypeId(FNV1a::Hash(T::TypeName));
#else       // This one may differ between diffrent compilers.
            return TypeId(Internal::TypeHash<typename RemoveConstReference<T>::Type>());
#endif
        }

        constexpr TypeId() noexcept = default;

        constexpr TypeId(const TypeId&) noexcept = default;

        constexpr TypeId(TypeId&&) noexcept = default;

        constexpr TypeId& operator=(const TypeId&) noexcept = default;

        constexpr TypeId& operator=(TypeId&&) noexcept = default;

        constexpr bool operator==(const TypeId& typeId) const noexcept { return typeId.mInternalId == mInternalId; }

        constexpr bool operator!=(const TypeId& typeId) const noexcept { return typeId.mInternalId != mInternalId; }

        constexpr bool operator<(const TypeId& typeId) const noexcept { return typeId.mInternalId < mInternalId; }

        constexpr bool operator>(const TypeId& typeId) const noexcept { return typeId.mInternalId > mInternalId; }

        constexpr bool IsValid() const noexcept { return mInternalId; }

    private:
        constexpr explicit TypeId(int internalId) noexcept : mInternalId(internalId) {}

        int mInternalId = 0;
    };
}
