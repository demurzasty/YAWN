#include <YAWN/Scene/UI/ViewportContainer.hpp>
#include <YAWN/Platform/Window.hpp>
#include <YAWN/Runtime/Console.hpp>
#include <YAWN/Graphics/Renderer.hpp>
#include <YAWN/Scene/Viewport.hpp>

using namespace YAWN;

void ViewportContainer::Enter() {
    Base::Enter();
}

void ViewportContainer::Update(float timeStep) {
    Base::Update(timeStep);

    if (GetChildCount() > 0) {
        if (const Ref<Viewport> viewport = CastTo<Viewport>(GetChild(0)); viewport) {
            viewport->SetSize(GetLocalSize());
        }
    }
}

void ViewportContainer::Draw() {
    Base::Draw();

    if (const Ref<Theme>& theme = GetTheme(); theme) {
        if (GetChildCount() > 0) {
            if (const Ref<Viewport> viewport = CastTo<Viewport>(GetChild(0)); viewport) {
                DrawTexture(Renderer::GetViewportColorTexture(viewport->GetId()),
                    Rectangle(GetGlobalPosition(), GetLocalSize()),
                    Rectangle(Vector2::Zero, GetLocalSize()),
                    Color::White,
                    true);
            }
        }
    }
}

void ViewportContainer::HandleEvent(const Event& event) {
    Base::HandleEvent(event);
}
