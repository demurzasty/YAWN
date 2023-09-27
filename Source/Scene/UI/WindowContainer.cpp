#include <YAWN/Scene/UI/WindowContainer.hpp>
#include <YAWN/Platform/Window.hpp>
#include <YAWN/Runtime/Console.hpp>

using namespace YAWN;

void WindowContainer::Enter() {
    Base::Enter();

    SetLocalRectangle(
        Rectangle(
            Vector2(GetPadding()),
            Vector2(Window::GetSize() - GetPadding() * 2.0f)
        )
    );
}

void WindowContainer::Update(float timeStep) {
    Base::Update(timeStep);

    if (GetChildCount() > 0) {
        if (const Ref<Control> control = CastTo<Control>(GetChild(0)); control) {
            control->SetLocalRectangle(
                Rectangle(
                    Vector2(GetPadding()),
                    Vector2(GetLocalSize() - GetPadding() * 2.0f)
                )
            );
        }
    }
}

void WindowContainer::Draw() {
    Base::Draw();

    if (const Ref<Theme>& theme = GetTheme(); theme) {
        DrawFillRect(GetGlobalRectangle(), theme->GetContainerColor());
    }
}

void WindowContainer::HandleEvent(const Event& event) {
    Base::HandleEvent(event);

    if (event.Type == EventType::WindowResize) {
        const WindowResizeEvent& windowResizeEvent = (const WindowResizeEvent&)event;
        SetLocalRectangle(
            Rectangle(
                Vector2(GetPadding()),
                Vector2(windowResizeEvent.Size - GetPadding() * 2.0f)
            )
        );
    }
}
