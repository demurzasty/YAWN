#pragma once 

#include "BoxContainer.hpp"
#include "../../Runtime/Signal.hpp"

namespace YAWN {
    class EditProperty : public BoxContainer {
        YAWN_OBJECT(EditProperty, BoxContainer);

    public:
        EditProperty();

        virtual ~EditProperty() = default;

        virtual void Enter() override;

        virtual void Exit() override;

        virtual void Update(float timeStep) override;

        virtual void Draw() override;

        void SetEditedObject(const Ref<Reference>& object);

        const Ref<Reference>& GetEditedObject() const;

        void SetEditedProperty(const String& property);

        const String& GetEditedProperty() const;

        Signal<const String&, const Variant&>& GetValueChangedSignal();

    private:
        void OnTextBoxValueChanged(const String& text);

        void Check();

    private:
        Ref<Reference> mEditedObject;
        String mEditedProperty;
        Signal<const String&, const Variant&> mValueChangedSignal;
    };
}