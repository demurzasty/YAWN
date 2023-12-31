#include <YAWN/Scene/UI/Popup.hpp>

using namespace YAWN;

void Popup::HandleEvent(const Event& event) {
    Base::HandleEvent(event);

    if (event.Type == EventType::MouseButtonDown) {
        const MouseButtonDownEvent& buttonEvent = (const MouseButtonDownEvent&)event;
        if (buttonEvent.Button == MouseButton::Left) {
            if (!Rectangle::Contains(GetGlobalRectangle(), buttonEvent.Position)) {
                GetParent()->RemoveChild(this);
            }
        }
    }
}

void Popup::Draw() {
    Base::Draw();

    if (const Ref<Theme>& theme = GetTheme(); theme) {
        DrawFillRect(GetGlobalRectangle(), theme->GetContainerColor());
        DrawRect(GetGlobalRectangle(), theme->GetFrameBorderColor());
    }
}
