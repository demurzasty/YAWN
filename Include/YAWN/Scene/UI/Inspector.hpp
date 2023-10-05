#pragma once 

#include "BoxContainer.hpp"

namespace YAWN {
    class Inspector : public BoxContainer {
        YAWN_OBJECT(Inspector, BoxContainer);

    public:
        Inspector();

        virtual ~Inspector() = default;

        void SetEditedObject(const Ref<Reference>& object);

        const Ref<Reference>& GetEditedObject() const;

    private:
        void AddEditProperty(const Ref<Field>& field);

        void OnPropertyValueChanged(const String& property, const Variant& value);

    private:
        Ref<Reference> mEditedObject;
    };
}