#include <YAWN/Scene/UI/WindowContainer.hpp>
#include <YAWN/Platform/Window.hpp>
#include <YAWN/Runtime/Console.hpp>

using namespace YAWN;

void WindowContainer::Enter() {
    Base::Enter();

    const Vector4& padding = GetPadding();
    SetLocalRectangle(
        Rectangle(
            Vector2(padding.X, padding.Y),
            Vector2(Window::GetSize() - Vector2(padding.X + padding.Z, padding.Y + padding.W))
        )
    );
}

void WindowContainer::Update(float timeStep) {
    Base::Update(timeStep);

    if (GetChildCount() > 0) {
        if (const Ref<Control> control = CastTo<Control>(GetChild(0)); control) {
            const Vector4& padding = GetPadding();
            control->SetLocalRectangle(
                Rectangle(
                    Vector2(padding.X, padding.Y),
                    Vector2(Window::GetSize() - Vector2(padding.X + padding.Z, padding.Y + padding.W))
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
        const Vector4& padding = GetPadding();
        SetLocalRectangle(
            Rectangle(
                Vector2(padding.X, padding.Y),
                Vector2(Window::GetSize() - Vector2(padding.X + padding.Z, padding.Y + padding.W))
            )
        );
    }
}
