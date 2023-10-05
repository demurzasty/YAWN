#include <YAWN/Scene/UI/Control.hpp>
#include <YAWN/Graphics/Renderer.hpp>
#include <YAWN/Runtime/ResourceManager.hpp>
#include <YAWN/Platform/Window.hpp>
#include <YAWN/Scene/Viewport.hpp>

using namespace YAWN;

Control::Control() {
    SetTheme(ResourceManager::GetDefaultTheme());
}

void Control::Enter() {
    Base::Enter();
}

void Control::Update(float timeStep) {
    Base::Update(timeStep);
}

void Control::Draw() {
    Base::Draw();
}

void Control::PostDraw() {
    Base::PostDraw();
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

Rectangle Control::GetGlobalClientRectangle() const {
    Rectangle globalRectangle = GetGlobalRectangle();

    return Rectangle(
        globalRectangle.Position + Vector2(mPadding.X, mPadding.Y),
        globalRectangle.Size - Vector2(mPadding.X + mPadding.Z, mPadding.Y + mPadding.W)
    );
}

Control* Control::GetControlParent() const {
    return mControlParent;
}

void Control::SetTheme(const Ref<Theme>& theme) {
    mTheme = theme;

    RequestRedraw();
}

const Ref<Theme>& Control::GetTheme() const {
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

void Control::SetPadding(const Vector4& padding) {
    mPadding = padding;

    RequestRedraw();
}

const Vector4& Control::GetPadding() const {
    return mPadding;
}

void Control::GrabFocus() {
    Ref<Viewport> viewport = GetViewport();
    YAWN_ASSERT(viewport);
    viewport->SetFocus(this);
}

void Control::LoseFocus() {
    Ref<Viewport> viewport = GetViewport();
    YAWN_ASSERT(viewport);

    if (viewport->GetFocus() == this) {
        viewport->SetFocus(nullptr);
    }
}

bool Control::HasFocus() const {
    Ref<Viewport> viewport = GetViewport();
    YAWN_ASSERT(viewport);
    return viewport->GetFocus() == this;
}

void Control::OnReparent() {
    Base::OnReparent();

    mControlParent = CastTo<Control>(GetParent());

    RequestRedraw();
}
