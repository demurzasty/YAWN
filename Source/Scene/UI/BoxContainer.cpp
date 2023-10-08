#include <YAWN/Scene/UI/BoxContainer.hpp>
#include <YAWN/Platform/Input.hpp>

using namespace YAWN;

BoxContainer::BoxContainer() {
    SetMargin(8.0f);
}

void BoxContainer::Update(float timeStep) {
    Base::Update(timeStep);

    if (!IsVisible()) {
        return;
    }

    if (HasExpandedChild()) {
        Vector2 minimumSize = Vector2::Zero;
        int expandedChildCount = 0;
        for (const Ref<Node>& child : GetChildren()) {
            if (const Ref<Control> control = CastTo<Control>(child); control && control->IsVisible()) {
                if (IsVertical()) {
                    if (control->IsVerticalExpand()) {
                        ++expandedChildCount;
                    } else {
                        minimumSize += control->GetLocalSize();
                    }
                } else {
                    if (control->IsHorizontalExpand()) {
                        ++expandedChildCount;
                    } else {
                        minimumSize += control->GetLocalSize();
                    }
                }
            }
        }

        int notExpandedChildCount = GetChildCount() - expandedChildCount;

        const Vector4& padding = GetPadding();
        Vector2 size = GetLocalSize() - Vector2(padding.X + padding.Z, padding.Y + padding.W);
        Vector2 diffSize = size - (minimumSize + GetMargin() * (notExpandedChildCount));
        Vector2 expandedElementSize = Vector2::Floor((diffSize - GetMargin() * float(expandedChildCount - 1)) / float(expandedChildCount));

        Vector2 position = Vector2(padding.X, padding.Y);
        for (const Ref<Node>& child : GetChildren()) {
            if (const Ref<Control> control = CastTo<Control>(child); control && control->IsVisible()) {
                if (IsVertical()) {
                    if (control->IsVerticalExpand()) {
                        control->SetLocalSize(Vector2(size.X, expandedElementSize.Y));
                        control->SetLocalPosition(position);
                        position.Y += expandedElementSize.Y + GetMargin();
                    } else {
                        control->SetLocalSize(Vector2(size.X, control->GetLocalSize().Y));
                        control->SetLocalPosition(position);
                        position.Y += control->GetLocalSize().Y + GetMargin();
                    }
                } else {
                    if (control->IsHorizontalExpand()) {
                        control->SetLocalSize(Vector2(expandedElementSize.X, size.Y));
                        control->SetLocalPosition(position);
                        position.X += expandedElementSize.X + GetMargin();
                    } else {
                        control->SetLocalSize(Vector2(control->GetLocalSize().X, size.Y));
                        control->SetLocalPosition(position);
                        position.X += control->GetLocalSize().X + GetMargin();
                    }
                }
            }
        }
    } else {
        const Vector4& padding = GetPadding();
        Vector2 size = GetLocalSize() - Vector2(padding.X + padding.Z, padding.Y + padding.W);
        Vector2 position = Vector2(padding.X, padding.Y);
        for (const Ref<Node>& child : GetChildren()) {
            if (const Ref<Control> control = CastTo<Control>(child); control && control->IsVisible()) {
                if (IsVertical()) {
                    control->SetLocalSize(Vector2(size.X, control->GetLocalSize().Y));

                    control->SetLocalPosition(position);
                    position.Y += control->GetLocalSize().Y + GetMargin();
                } else {
                    control->SetLocalSize(Vector2(control->GetLocalSize().X, size.Y));

                    control->SetLocalPosition(position);
                    position.X += control->GetLocalSize().X + GetMargin();
                }
            }
        }
    }
}

void BoxContainer::HandleEvent(const Event& event) {
    Base::HandleEvent(event);

    if (event.Type == EventType::MouseButtonDown ||
        event.Type == EventType::MouseButtonUp ||
        event.Type == EventType::MouseMove) {
        const Vector2& mousePosition = Input::GetMousePosition();
        if (event.Type == EventType::MouseButtonDown && Rectangle::Contains(GetGlobalRectangle(), mousePosition)) {
            event.Consume();
            LoseFocus();
        }

        if (IsSplitter()) { 
            if (Rectangle::Contains(GetGlobalRectangle(), mousePosition)) {
                if (Input::IsMouseButtonPressed(MouseButton::Left)) {
                    for (int i = 0; i < GetChildCount() - 1; ++i) {
                        const Ref<Node>& child = GetChild(i);
                        if (const Ref<Control> control = CastTo<Control>(child); control) {
                            Vector2 position = control->GetGlobalPosition();
                            Vector2 size = control->GetLocalSize();
                            if (IsVertical()) {
                                if (mousePosition.Y > position.Y + size.Y && mousePosition.Y < position.Y + size.Y + GetMargin()) {
                                    mSelectedSplitter = GetChildren().Find(child);
                                    mSplitMousePosition = mousePosition;
                                    mSplitSizeLeft = control->GetLocalSize();
                                    mSplitSizeRight = CastTo<Control>(GetChild(mSelectedSplitter + 1))->GetLocalSize();
                                    break;
                                }
                            } else {
                                if (mousePosition.X > position.X + size.X && mousePosition.X < position.X + size.X + GetMargin()) {
                                    mSelectedSplitter = GetChildren().Find(child);
                                    mSplitMousePosition = mousePosition;
                                    mSplitSizeLeft = control->GetLocalSize();
                                    mSplitSizeRight = CastTo<Control>(GetChild(mSelectedSplitter + 1))->GetLocalSize();
                                    break;
                                }
                            }
                        }
                    }
                }

                if (Input::IsMouseButtonDown(MouseButton::Left) && mSelectedSplitter > -1) {
                    Vector2 splitOffset = mousePosition - mSplitMousePosition;

                    if (mSelectedSplitter + 1 < GetChildCount()) {
                        Ref<Control> leftControl = CastTo<Control>(GetChild(mSelectedSplitter));
                        Ref<Control> rightControl = CastTo<Control>(GetChild(mSelectedSplitter + 1));

                        if (IsVertical()) {
                            leftControl->SetLocalSize(Vector2(mSplitSizeLeft.X, mSplitSizeLeft.Y + splitOffset.Y));
                            rightControl->SetLocalSize(Vector2(mSplitSizeRight.X, mSplitSizeRight.Y - splitOffset.Y));
                        } else {
                            leftControl->SetLocalSize(Vector2(mSplitSizeLeft.X + splitOffset.X, mSplitSizeLeft.Y));
                            rightControl->SetLocalSize(Vector2(mSplitSizeRight.X - splitOffset.X, mSplitSizeRight.Y));
                        }
                    }
                }
            }

            if (Input::IsMouseButtonReleased(MouseButton::Left)) {
                mSelectedSplitter = -1;
            }
        }
    }
}

void BoxContainer::Draw() {
    Base::Draw();

    if (const Ref<Theme>& theme = GetTheme(); theme) {
        // DrawFillRect(GetGlobalRectangle(), theme->GetContainerColor());

        if (IsSplitter()) {
            for (int i = 0; i < GetChildCount() - 1; ++i) {
                const Ref<Node>& child = GetChild(i);
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

void BoxContainer::SetSplitter(bool splitter) {
    mSplitter = splitter;
}

bool BoxContainer::IsSplitter() const {
    return mSplitter;
}

bool BoxContainer::HasExpandedChild() const {
    for (const Ref<Node>& child : GetChildren()) {
        if (const Ref<Control> control = CastTo<Control>(child); control) {
            if (IsVertical()) {
                if (control->IsVerticalExpand()) {
                    return true;
                }
            } else {
                if (control->IsHorizontalExpand()) {
                    return true;
                }
            }
        }
    }

    return false;
}
