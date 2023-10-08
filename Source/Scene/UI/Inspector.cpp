#include <YAWN/Scene/UI/Inspector.hpp>
#include <YAWN/Reflection/Types.hpp>
#include <YAWN/Runtime/Console.hpp>
#include <YAWN/Scene/UI/EditProperty.hpp>

using namespace YAWN;

Inspector::Inspector() {
    SetVertical(true);
    SetPadding(8.0f);
    SetMargin(0.0f);
}

void Inspector::SetEditedObject(const Ref<Reference>& object) {
    mEditedObject = object;

    RemoveAllChildren();

    if (Ref<Type> type = Types::GetType(object->GetTypeId()); type) {
        type->EnumerateFields(Delegate<void(const Ref<Field>& field)>::Bind<&Inspector::AddEditProperty>(this));
    }
}

const Ref<Reference>& Inspector::GetEditedObject() const {
    return mEditedObject;
}

void Inspector::AddEditProperty(const Ref<Field>& field) {
    Ref<EditProperty> editProperty = new EditProperty();
    editProperty->SetEditedObject(mEditedObject);
    editProperty->SetEditedProperty(field->GetName());
    editProperty->GetValueChangedSignal().Connect<&Inspector::OnPropertyValueChanged>(this);
    AddChild(editProperty);
}

void Inspector::OnPropertyValueChanged(const String& property, const Variant& value) {
    if (!mEditedObject) {
        return;
    }

    Ref<Type> type = Types::GetType(mEditedObject->GetTypeId());
    if (!type) {
        return;
    }

    Ref<Field> field = type->GetField(property);
    if (!field) {
        return;
    }

    if (field->GetType() == VariantType::Null) {
        return;
    }

    if (field->GetType() != value.GetType()) {
        return;
    }

    field->Set(mEditedObject.Get(), value);
}
