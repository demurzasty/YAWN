#include <YAWN/Scene/UI/GridContainer.hpp>
#include <YAWN/Platform/Input.hpp>

using namespace YAWN;

GridContainer::GridContainer() {
    SetPadding(8.0f);
    SetMargin(8.0f);
}

void GridContainer::Update(float timeStep) {
    Base::Update(timeStep);

    Vector2 offset = Vector2(GetPadding().X, GetPadding().Y);
    for (const Ref<Node>& child : GetChildren()) {
        if (Ref<Control> control = CastTo<Control>(child); control) {
            control->SetLocalPosition(offset);
            control->SetLocalSize(GetCellSize());

            offset.X += GetCellSize().X + GetMargin();

            if (offset.X > GetLocalSize().X - GetCellSize().X - GetPadding().X) {
                offset.X = GetPadding().X;
                offset.Y += GetCellSize().Y + GetMargin();
            }
        }
    }
}

void GridContainer::SetCellSize(const Vector2& cellSize) {
    mCellSize = cellSize;

    RequestRedraw();
}

const Vector2& GridContainer::GetCellSize() const {
    return mCellSize;
}
