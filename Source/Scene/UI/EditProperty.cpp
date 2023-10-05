#include <YAWN/Scene/UI/EditProperty.hpp>

using namespace YAWN;

EditProperty::EditProperty() {
}

void EditProperty::Exit() {
    Base::Exit();

    mEditedObject = nullptr;
    mEditedProperty = L"";
}

void EditProperty::Update(float timeStep) {
    Base::Update(timeStep);
}

void EditProperty::Draw() {
    Base::Draw();
}

void EditProperty::SetEditedObject(const Ref<Reference>& object) {
    mEditedObject = object;
}

const Ref<Reference>& EditProperty::GetEditedObject() const {
    return mEditedObject;
}

void EditProperty::SetEditedProperty(const String& property) {
    mEditedProperty = property;
}

const String& EditProperty::GetEditedProperty() const {
    return mEditedProperty;
}
