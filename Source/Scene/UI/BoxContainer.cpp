#include <YAWN/Scene/UI/BoxContainer.hpp>
#include <YAWN/Platform/Input.hpp>

using namespace YAWN;

BoxContainer::BoxContainer() {
    SetMargin(8.0f);
}

void BoxContainer::Update(float timeStep) {
    Base::Update(timeStep);

    //if (IsSplitter()) {
    //    const Vector2& mousePosition = Input::GetMousePosition();
    //    if (GetGlobalRectangle().Contains(mousePosition)) {
    //        if (Input::IsMouseButtonPressed(MouseButton::Left)) {
    //           // float offset = 0.0f;
    //            for (const Ref<Node>& child : GetChildren()) {
    //                if (const Ref<Control> control = CastTo<Control>(child); control) {
    //                    Vector2 position = control->GetGlobalPosition();
    //                    Vector2 size = control->GetLocalSize();
    //                    if (IsVertical()) {
    //                        if (mousePosition.Y > position.Y + size.Y && mousePosition.Y < position.Y + size.Y + GetMargin()) {
    //                            mSelectedSplitter = GetChildren().Find(child);
    //                            mLastMousePosition = mousePosition;
    //                            break;
    //                        }
    //                    } else {
    //                        if (mousePosition.X > position.X + size.X && mousePosition.X < position.X + size.X + GetMargin()) {
    //                            mSelectedSplitter = GetChildren().Find(child);
    //                            mLastMousePosition = mousePosition;
    //                            break;
    //                        }
    //                    }
    //                }
    //            }
    //        }

    //        if (Input::IsMouseButtonDown(MouseButton::Left) && mSelectedSplitter > -1) {
    //            Vector2 offset = mousePosition - mLastMousePosition;

    //            if (mSelectedSplitter + 1 < GetChildren().GetSize()) {
    //                Ref<Control> leftControl = CastTo<Control>(GetChildren()[mSelectedSplitter]);
    //                Ref<Control> rightControl = CastTo<Control>(GetChildren()[mSelectedSplitter + 1]);

    //                if (IsVertical()) {
    //                    leftControl->SetLocalSize(Vector2(leftControl->GetLocalSize().X, leftControl->GetLocalSize().Y + offset.Y));
    //                    rightControl->SetLocalSize(Vector2(rightControl->GetLocalSize().X, rightControl->GetLocalSize().Y - offset.Y));
    //                } else {
    //                    leftControl->SetLocalSize(Vector2(leftControl->GetLocalSize().X + offset.X, leftControl->GetLocalSize().Y));
    //                    rightControl->SetLocalSize(Vector2(rightControl->GetLocalSize().X - offset.X, rightControl->GetLocalSize().Y));
    //                }
    //            }

    //            mLastMousePosition = mousePosition;
    //        }
    //    }

    //    if (Input::IsMouseButtonReleased(MouseButton::Left)) {
    //        mSelectedSplitter = -1;
    //    }
    //}

    //Vector2 offset = Vector2(GetPadding());
    //for (const Ref<Node>& child : GetChildren()) {
    //    if (const Ref<Control> control = CastTo<Control>(child); control) {
    //        control->SetLocalPosition(offset);

    //        if (IsVertical()) {
    //            offset.Y += control->GetLocalSize().Y + GetMargin();
    //        } else {
    //            offset.X += control->GetLocalSize().X + GetMargin();
    //        }
    //    }
    //}

    //for (const Ref<Node>& child : GetChildren()) {
    //    if (const Ref<Control> control = CastTo<Control>(child); control) {
    //        if (control->IsVerticalExpand() || control->IsHorizontalExpand()) {
    //            Vector2 size = control->GetLocalSize();

    //            if (control->IsVerticalExpand()) {
    //                //if (GetChildCount() == 1 || control->IsLastChild()) {
    //                //    size.Y = GetLocalSize().Y - control->GetLocalPosition().Y - GetPadding();
    //                //} else {
    //                //    if (Ref<Control> nextControl = CastTo<Control>(GetChild(control->GetIndex() + 1)); nextControl) {
    //                //        size.Y = GetLocalSize().Y - control->GetLocalPosition().Y - GetPadding() - nextControl->GetLocalSize().Y;
    //                //    }
    //                //}

    //                if (IsLastChild()) {
    //                    size.Y = GetLocalSize().Y - control->GetLocalPosition().Y - GetPadding();
    //                } else if (IsVertical()) {
    //                    if (Ref<Control> nextControl = CastTo<Control>(GetChild(control->GetIndex() + 1)); nextControl) {
    //                        size.Y = GetLocalSize().Y - control->GetLocalPosition().Y - GetPadding() - nextControl->GetLocalSize().Y;
    //                    }
    //                }
    //            }

    //            if (control->IsHorizontalExpand()) {
    //                // if (IsLastChild()) {
    //                if (control->IsLastChild()) {
    //                    size.X = GetLocalSize().X - control->GetLocalPosition().X - GetPadding();
    //                } else  if (!IsVertical()) {
    //                    if (Ref<Control> nextControl = CastTo<Control>(GetChild(control->GetIndex() + 1)); nextControl) {
    //                        size.X = GetLocalSize().X - control->GetLocalPosition().X - GetPadding() - nextControl->GetLocalSize().X;
    //                    }
    //                }
    //                // }
    //            }

    //            control->SetLocalSize(size);
    //        }
    //    }
    //}

    if (HasExpandedChild()) {
        Vector2 size = GetLocalSize();
        Vector2 elementSize = Vector2::Floor((size - GetMargin() * (GetChildCount() - 1)) / GetChildCount());

        Vector2 minimumSize = Vector2::Zero;
        int expandedChildCount = 0;
        for (const Ref<Node>& child : GetChildren()) {
            if (const Ref<Control> control = CastTo<Control>(child); control) {
                if (IsVertical()) {
                    if (control->IsVerticalExpand()) {
                        ++expandedChildCount;
                    } else {
                        minimumSize += control->GetMinimumSize();
                    }
                } else {
                    if (control->IsHorizontalExpand()) {
                        ++expandedChildCount;
                    } else {
                        minimumSize += control->GetMinimumSize();
                    }
                }
            }
        }

        int notExpandedChildCount = GetChildCount() - expandedChildCount;

        Vector2 diffSize = size - (minimumSize + GetMargin() * (notExpandedChildCount - 1));
        Vector2 expandedElementSize = Vector2::Floor((diffSize - GetMargin() * (expandedChildCount - 1)) / expandedChildCount);

        Vector2 position = Vector2::Zero;
        for (const Ref<Node>& child : GetChildren()) {
            if (const Ref<Control> control = CastTo<Control>(child); control) {
                if (IsVertical()) {
                    if (control->IsLastChild()) {
                        control->SetLocalSize(Vector2(size.X, size.Y - position.Y));
                        control->SetLocalPosition(position);
                    } else if (control->IsVerticalExpand()) {
                        control->SetLocalSize(Vector2(size.X, expandedElementSize.Y - GetMargin()));
                        control->SetLocalPosition(position);
                        position.Y += expandedElementSize.Y;
                    } else {
                        control->SetLocalSize(Vector2(size.X, control->GetMinimumSize().Y));
                        control->SetLocalPosition(position);
                        position.Y += control->GetMinimumSize().Y + GetMargin();
                    }
                } else {
                    if (control->IsLastChild()) {
                        control->SetLocalSize(Vector2(size.X - position.X, size.Y));
                        control->SetLocalPosition(position);
                    } else if (control->IsHorizontalExpand()) {
                        control->SetLocalSize(Vector2(expandedElementSize.X - GetMargin(), size.Y));
                        control->SetLocalPosition(position);
                        position.X += expandedElementSize.X ;
                    } else {
                        control->SetLocalSize(Vector2(control->GetMinimumSize().X, size.Y));
                        control->SetLocalPosition(position);
                        position.X += control->GetMinimumSize().X + GetMargin();
                    }
                }
            }
        }
    } else {
        Vector2 size = GetLocalSize();
        Vector2 position = Vector2::Zero;
        for (const Ref<Node>& child : GetChildren()) {
            if (const Ref<Control> control = CastTo<Control>(child); control) {
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

void BoxContainer::Draw() {
    Base::Draw();

    if (const Ref<Theme>& theme = GetTheme(); theme) {
        DrawFillRect(GetGlobalRectangle(), theme->GetContainerColor());

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
