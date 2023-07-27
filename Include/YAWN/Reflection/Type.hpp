#pragma once 

#include "Field.hpp"

#include "../Core/Map.hpp"
#include "../Core/FNV1a.hpp"
#include "../Core/String.hpp"
#include "../Runtime/Delegate.hpp"
#include "../Runtime/Object.hpp"

namespace YAWN {
    class Type {
    public:
        void SetName(const String& string);

        const String& GetName() const;

        void AddTag(const String& tag);

        bool HasTag(const String& tag) const;

        void AddField(const String& name, const Field& field);

        bool HasField(const String& name);

        const Field& GetField(const String& name);

        void EnumerateFields(const Delegate<void(const String&, const Field&)>& delegate);

        void SetConstructor(Ref<Reference>(*constructor)());

        Ref<Reference> Construct() const;

        void SetBase(int id);

        int GetBase() const;

        bool IsDerivedFrom(int id) const;

    private:
        String mName;
        Array<String> mTags;
        Map<String, Field> mFields;
        Ref<Reference>(*mConstructor)();
        int mBase = 0;
    };
}
