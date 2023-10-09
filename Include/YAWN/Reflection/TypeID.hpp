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

    class TypeID {
    public:
        template<typename T>
        static constexpr int Hash() {
            return Internal::TypeHash<typename RemoveConstReference<T>::Type>();
        }
    };
}
