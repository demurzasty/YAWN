#pragma once 

#include "Field.hpp"

#include "../Core/Map.hpp"
#include "../Core/FNV1a.hpp"
#include "../Core/String.hpp"
#include "../Runtime/Delegate.hpp"
#include "../Runtime/Object.hpp"
#include "../Runtime/Reference.hpp"

namespace YAWN {
    class Type : public Reference {
    public:
        virtual ~Type() = default;

        void SetId(TypeId id);

        TypeId GetId() const;

        void SetName(const String& string);

        const String& GetName() const;

        void AddTag(const String& tag);

        bool HasTag(const String& tag) const;

        void AddField(const Ref<Field>& field);

        bool HasField(const String& name);

        Ref<Field> GetField(const String& name);

        void EnumerateFields(const Delegate<void(const Ref<Field>&)>& delegate);

        void SetConstructor(Ref<Reference>(*constructor)());

        Ref<Reference> Construct() const;

        void SetBase(TypeId id);

        TypeId GetBase() const;

        bool IsDerivedFrom(TypeId id) const;

    private:
        String mName;
        Array<String> mTags;
        Array<Ref<Field>> mFields;
        Ref<Reference>(*mConstructor)() = nullptr;
        TypeId mId;
        TypeId mBase;
    };
}
