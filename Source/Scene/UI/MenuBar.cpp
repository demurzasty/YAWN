#include <YAWN/Scene/UI/MenuBar.hpp>

using namespace YAWN;

void MenuBar::Enter() {
    Base::Enter();

    SetMargin(8.0f);
    SetPadding(4.0f);
}

void MenuBar::Update(float timeStep) {
    SetLocalSize(Vector2(GetLocalSize().X, 24.0f + GetPadding() * 2.0f));

    for (const Ref<Node>& child : GetChildren()) {
        if (const Ref<Control> control = CastTo<Control>(child); control) {
            control->SetVerticalExpand(true);
        }
    }

    Base::Update(timeStep);
}
