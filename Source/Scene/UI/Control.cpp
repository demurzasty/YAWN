#include <YAWN/Scene/UI/Control.hpp>
#include <YAWN/Graphics/Renderer.hpp>
#include <YAWN/Runtime/ResourceManager.hpp>

using namespace YAWN;

void Control::Enter() {
    Base::Enter();

    if (!GetTheme()) {
        SetTheme(ResourceManager::GetDefaultTheme());
    }
}

void Control::Update(float timeStep) {
    Base::Update(timeStep);

    if (mVerticalExpand || mHorizontalExpand) {
        Vector2 size = GetLocalSize();

        if (const Control* control = GetControlParent(); control) {
            if (mVerticalExpand) {
                size.Y = control->GetLocalSize().Y - GetLocalPosition().Y - control->GetPadding();
            }

            if (mHorizontalExpand) {
                size.X = control->GetLocalSize().X - GetLocalPosition().X - control->GetPadding();
            }
        }

        SetLocalSize(size);
    }
}

void Control::Draw() {
    Base::Draw();
}

void Control::SetLocalSize(const Vector2& size) {
    mLocalSize = size;

    RequestRedraw();
}

const Vector2& Control::GetLocalSize() const {
    return mLocalSize;
}

void Control::SetLocalRectangle(const Rectangle& rectangle) {
    SetLocalPosition(rectangle.GetPosition());
    SetLocalSize(rectangle.GetSize());

    RequestRedraw();
}

Rectangle Control::GetLocalRectangle() const {
    return Rectangle(GetLocalPosition(), GetLocalSize());
}

Rectangle Control::GetGlobalRectangle() const {
    return Rectangle(GetGlobalPosition(), GetLocalSize());
}

Control* Control::GetControlParent() const {
    return mControlParent;
}

void Control::SetTheme(const Ref<Theme>& theme) {
    mTheme = theme;

    RequestRedraw();
}

const Ref<Theme> Control::GetTheme() const {
    return mTheme;
}

void Control::SetHorizontalExpand(bool expand) {
    mHorizontalExpand = expand;

    RequestRedraw();
}

bool Control::IsHorizontalExpand() const {
    return mHorizontalExpand;
}

void Control::SetVerticalExpand(bool expand) {
    mVerticalExpand = expand;

    RequestRedraw();
}

bool Control::IsVerticalExpand() const {
    return mVerticalExpand;
}

void Control::SetPadding(float padding) {
    mPadding = padding;

    RequestRedraw();
}

float Control::GetPadding() const {
    return mPadding;
}

void Control::OnReparent() {
    Base::OnReparent();

    mControlParent = CastTo<Control>(GetParent());
}
