#pragma once 

#include "Control.hpp"

namespace YAWN {
    class EditProperty : public Control {
        YAWN_OBJECT(EditProperty, Control);

    public:
        EditProperty();

        virtual ~EditProperty() = default;

        virtual void Exit() override;

        virtual void Update(float timeStep) override;

        virtual void Draw() override;

        void SetEditedObject(const Ref<Reference>& object);

        const Ref<Reference>& GetEditedObject() const;

        void SetEditedProperty(const String& property);

        const String& GetEditedProperty() const;

    private:
        Ref<Reference> mEditedObject;
        String mEditedProperty;
    };
}