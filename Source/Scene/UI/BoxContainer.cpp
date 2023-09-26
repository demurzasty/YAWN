#include <YAWN/Scene/UI/BoxContainer.hpp>
#include <YAWN/Platform/Input.hpp>

using namespace YAWN;

void BoxContainer::Update(float timeStep) {
    Base::Update(timeStep);

    if (IsSplitter()) {
        const Vector2& mousePosition = Input::GetMousePosition();
        if (GetGlobalRectangle().Contains(mousePosition)) {
            if (Input::IsMouseButtonPressed(MouseButton::Left)) {
               // float offset = 0.0f;
                for (const Ref<Node>& child : GetChildren()) {
                    if (const Ref<Control> control = CastTo<Control>(child); control) {
                        Vector2 position = control->GetGlobalPosition();
                        Vector2 size = control->GetLocalSize();
                        if (IsVertical()) {
                            if (mousePosition.Y > position.Y + size.Y && mousePosition.Y < position.Y + size.Y + GetMargin()) {
                                mSelectedSplitter = GetChildren().Find(child);
                                mLastMousePosition = mousePosition;
                                break;
                            }
                        } else {
                            if (mousePosition.X > position.X + size.X && mousePosition.X < position.X + size.X + GetMargin()) {
                                mSelectedSplitter = GetChildren().Find(child);
                                mLastMousePosition = mousePosition;
                                break;
                            }
                        }
                    }
                }
            }

            if (Input::IsMouseButtonDown(MouseButton::Left) && mSelectedSplitter > -1) {
                Vector2 offset = mousePosition - mLastMousePosition;

                if (mSelectedSplitter + 1 < GetChildren().GetSize()) {
                    Ref<Control> leftControl = CastTo<Control>(GetChildren()[mSelectedSplitter]);
                    Ref<Control> rightControl = CastTo<Control>(GetChildren()[mSelectedSplitter + 1]);

                    if (IsVertical()) {
                        leftControl->SetLocalSize(Vector2(leftControl->GetLocalSize().X, leftControl->GetLocalSize().Y + offset.Y));
                        rightControl->SetLocalSize(Vector2(rightControl->GetLocalSize().X, rightControl->GetLocalSize().Y - offset.Y));
                    } else {
                        leftControl->SetLocalSize(Vector2(leftControl->GetLocalSize().X + offset.X, leftControl->GetLocalSize().Y));
                        rightControl->SetLocalSize(Vector2(rightControl->GetLocalSize().X - offset.X, rightControl->GetLocalSize().Y));
                    }
                }

                mLastMousePosition = mousePosition;
            }
        }

        if (Input::IsMouseButtonReleased(MouseButton::Left)) {
            mSelectedSplitter = -1;
        }
    }

    Vector2 offset = Vector2(GetPadding());
    for (const Ref<Node>& child : GetChildren()) {
        if (const Ref<Control> control = CastTo<Control>(child); control) {
            control->SetLocalPosition(offset);

            if (IsVertical()) {
                offset.Y += control->GetLocalSize().Y + GetMargin();
            } else {
                offset.X += control->GetLocalSize().X + GetMargin();
            }
        }
    }
}

void BoxContainer::Draw() {
    Base::Draw();

    if (const Ref<Theme>& theme = GetTheme(); theme) {
        DrawFillRect(GetGlobalRectangle(), theme->GetContainerColor());

        if (IsSplitter()) {
            for (const Ref<Node>& child : GetChildren()) {
                if (const Ref<Control> control = CastTo<Control>(child); control) {
                    Rectangle rectangle;
                    if (IsVertical()) {
                        rectangle.Position.X = control->GetGlobalPosition().X;
                        rectangle.Position.Y = control->GetGlobalPosition().Y + control->GetLocalSize().Y;
                        rectangle.Size.X = control->GetLocalSize().X;
                        rectangle.Size.Y = GetMargin();
                    } else {
                        rectangle.Position.X = control->GetGlobalPosition().X + control->GetLocalSize().X;
                        rectangle.Position.Y = control->GetGlobalPosition().Y;
                        rectangle.Size.X = GetMargin();
                        rectangle.Size.Y = control->GetLocalSize().Y;
                    }

                    DrawFillRect(rectangle, GetChildren().Find(child) == mSelectedSplitter ? theme->GetActiveSplitterColor() : theme->GetSplitterColor());
                }
            }
        }
    }
}

void BoxContainer::SetVertical(bool vertical) {
    mVertical = vertical;
}

bool BoxContainer::IsVertical() const {
    return mVertical;
}

void BoxContainer::SetMargin(float margin) {
    mMargin = margin;
}

float BoxContainer::GetMargin() const {
    if (IsSplitter()) {
        return 8.0f;
    }

    return mMargin;
}

void BoxContainer::SetSplitter(bool splitter) {
    mSplitter = splitter;
}

bool BoxContainer::IsSplitter() const {
    return mSplitter;
}
