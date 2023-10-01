#include <YAWN/Scene/UI/MenuBar.hpp>

using namespace YAWN;

MenuBar::MenuBar() {
    SetMargin(8.0f);
    SetPadding(4.0f);

    const Vector4& padding = GetPadding();
    SetLocalSize(Vector2(24.0f) + Vector2(padding.X + padding.Z, padding.Y + padding.W));
}

void MenuBar::Enter() {
    Base::Enter();
}

void MenuBar::Update(float timeStep) {
    Base::Update(timeStep);

    for (const Ref<Node>& child : GetChildren()) {
        if (const Ref<Control> control = CastTo<Control>(child); control) {
            control->SetVerticalExpand(true);
        }
    }
}
