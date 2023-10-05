#include <YAWN/Scene/UI/EditProperty.hpp>
#include <YAWN/Scene/UI/Label.hpp>
#include <YAWN/Scene/UI/TextBox.hpp>
#include <YAWN/Reflection/Types.hpp>
#include <YAWN/Core/Number.hpp>

using namespace YAWN;

EditProperty::EditProperty() {
    SetMinimumSize(Vector2(16.0f, 64.0f));
    SetVertical(true);
}

void EditProperty::Enter() {
    Base::Enter();

    Check();
}

void EditProperty::Exit() {
    Base::Exit();

    RemoveAllChildren();

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

    RemoveAllChildren();

    Check();
}

const Ref<Reference>& EditProperty::GetEditedObject() const {
    return mEditedObject;
}

void EditProperty::SetEditedProperty(const String& property) {
    mEditedProperty = property;

    RemoveAllChildren();

    Check();
}

const String& EditProperty::GetEditedProperty() const {
    return mEditedProperty;
}

Signal<const String&, const Variant&>& EditProperty::GetValueChangedSignal() {
    return mValueChangedSignal;
}

void EditProperty::OnTextBoxValueChanged(const String& text) {
    mValueChangedSignal.Emit(mEditedProperty, text);
}

void EditProperty::Check() {
    if (!mEditedObject) {
        return;
    }

    if (mEditedProperty.IsEmpty()) {
        return;
    }

    if (GetChildCount() > 0) {
        return;
    }

    Ref<Type> type = Types::GetType(mEditedObject->GetTypeId());
    if (!type) {
        return;
    }

    Ref<Field> field = type->GetField(mEditedProperty);
    if (!field) {
        return;
    }

    Ref<Label> label = new Label();
    label->SetText(mEditedProperty);
    label->SetMinimumSize(Vector2(16.0f, 16.0f));
    AddChild(label);

    if (field->GetType() == VariantType::String) {
        Ref<TextBox> textBox = new TextBox();
        textBox->SetText(field->Get(mEditedObject.Get()));
        textBox->GetValueChangedSignal().Connect<&EditProperty::OnTextBoxValueChanged>(this);
        AddChild(textBox);
    }

    if (field->GetType() == VariantType::Vector3) {
        Ref<BoxContainer> container = new BoxContainer();
        container->SetMinimumSize(32.0f);

        Ref<TextBox> textBox = new TextBox();
        textBox->SetHorizontalExpand(true);
        textBox->SetText(Number::ToString(field->Get(mEditedObject.Get()).AsVector3().X));
        container->AddChild(textBox);

        textBox = new TextBox();
        textBox->SetHorizontalExpand(true);
        textBox->SetText(Number::ToString(field->Get(mEditedObject.Get()).AsVector3().Y));
        container->AddChild(textBox);

        textBox = new TextBox();
        textBox->SetHorizontalExpand(true);
        textBox->SetText(Number::ToString(field->Get(mEditedObject.Get()).AsVector3().Z));
        container->AddChild(textBox);

        AddChild(container);
    }
}