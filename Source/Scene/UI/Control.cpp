#include <YAWN/Scene/UI/Control.hpp>
#include <YAWN/Graphics/Renderer.hpp>
#include <YAWN/Runtime/ResourceManager.hpp>
#include <YAWN/Platform/Window.hpp>

using namespace YAWN;

void Control::Enter() {
    Base::Enter();

    if (!GetTheme()) {
        SetTheme(ResourceManager::GetDefaultTheme());
    }
}

void Control::Update(float timeStep) {
    Base::Update(timeStep);
}

void Control::Draw() {
    Base::Draw();
}

void Control::SetLocalSize(const Vector2& size) {
    mLocalSize = Vector2::Max(size, mMinimumSize);

    RequestRedraw();
}

const Vector2& Control::GetLocalSize() const {
    return mLocalSize;
}

void Control::SetMinimumSize(const Vector2& size) {
    mMinimumSize = size;
    mLocalSize = Vector2::Max(mLocalSize, mMinimumSize);

    RequestRedraw();
}

const Vector2& Control::GetMinimumSize() const {
    return mMinimumSize;
}

void Control::SetLocalRectangle(const Rectangle& rectangle) {
    SetLocalPosition(rectangle.Position);
    SetLocalSize(rectangle.Size);

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
