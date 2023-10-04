#include <YAWN/Scene/UI/Tree.hpp>
#include <YAWN/Platform/Input.hpp>

using namespace YAWN;

TreeItem::TreeItem(Tree* tree, const Ref<TreeItem>& parent) : mTree(tree) {
    if (parent) {
        parent->mChildren.Add(this);
    }
}

void TreeItem::SetText(const String& text) {
    mText = text;

    mTree->RequestRedraw();
}

const String& TreeItem::GetText() const {
    return mText;
}

void TreeItem::SetGlobalRectangle(const Rectangle& rectangle) {
    mRectangle = rectangle;
}

const Rectangle& TreeItem::GetGlobalRectangle() const {
    return mRectangle;
}

const Array<Ref<TreeItem>>& TreeItem::GetChildren() const {
    return mChildren;
}

void TreeItem::SetCollapsed(bool collapsed) {
    mCollapsed = collapsed;

    mTree->RequestRedraw();
}

bool TreeItem::IsCollapsed() const {
    return mCollapsed;
}

void Tree::HandleEvent(const Event& event) {
    Base::HandleEvent(event);

    if (event.Type == EventType::MouseButtonDown ||
        event.Type == EventType::MouseButtonUp ||
        event.Type == EventType::MouseMove) {
        Vector2 offset = Vector2(8.0f, 0.0f);
        HandleEvent(event, mRoot, offset);
    }
}

void Tree::HandleEvent(const Event& event, const Ref<TreeItem>& item, Vector2& offset) {
    Rectangle rectangle;
    rectangle.Position = GetGlobalPosition() + Vector2(0.0f, offset.Y);
    rectangle.Size = Vector2(GetLocalSize().X - 1.0f, 24.0f);

    if (event.Type == EventType::MouseButtonDown) {
        const MouseButtonDownEvent& buttonEvent = (const MouseButtonDownEvent&)event;

        if (buttonEvent.Button == MouseButton::Left && Rectangle::Contains(rectangle, buttonEvent.Position)) {
            item->SetCollapsed(!item->IsCollapsed());

            event.Consume();
        }
    }


    offset += Vector2(16.0f, rectangle.Size.Y);

    if (!item->IsCollapsed()) {
        for (const Ref<TreeItem>& child : item->GetChildren()) {
            HandleEvent(event, child, offset);
        }
    }

    offset.X -= 16.0f;
}

void Tree::Draw() {
    Base::Draw();

    if (const Ref<Theme>& theme = GetTheme(); theme) {
        Vector2 offset = Vector2(8.0f, 0.0f);
        bool isOdd = false;
        Draw(theme, mRoot, offset, isOdd);
    }
}

void Tree::Draw(const Ref<Theme>& theme, const Ref<TreeItem>& item, Vector2& offset, bool& isOdd) {
    Rectangle fillRectangle;
    fillRectangle.Position = GetGlobalPosition() + Vector2(0.0f, offset.Y);
    fillRectangle.Size = Vector2(GetLocalSize().X - 1.0f, 24.0f);
    DrawFillRect(fillRectangle, isOdd ? theme->GetTreeItemOddColor() : theme->GetTreeItemEvenColor());

    Vector2 textSize = theme->GetDefaultFont()->GetTextSize(item->GetText(), 16);

    Vector2 position = Vector2::Zero;
    
    if (!item->GetChildren().IsEmpty()) {
        position = GetGlobalPosition() + offset;
        position.Y += 24.0f / 2.0f - 16.0f / 2.0f;

        if (item->IsCollapsed()) {
            DrawTexture(theme->GetIconsTexture()->GetId(), Rectangle(position, Vector2(16.0f)), Rectangle(8.0f * 50.0f, 6.0f * 50.0f, 50.0f, 50.0f), Color::White);
        } else {
            DrawTexture(theme->GetIconsTexture()->GetId(), Rectangle(position, Vector2(16.0f)), Rectangle(7.0f * 50.0f, 7.0f * 50.0f, 50.0f, 50.0f), Color::White);
        }

    }

    position = GetGlobalPosition() + offset;
    position.X += 24.0f;
    position.Y += 24.0f / 2.0f - textSize.Y / 2.0f;

    DrawText(theme->GetDefaultFont(), 16, position, item->GetText(), Color::White);

    offset += Vector2(16.0f, 24.0f);

    isOdd = !isOdd;

    if (!item->IsCollapsed()) {
        for (const Ref<TreeItem>& child : item->GetChildren()) {
            Draw(theme, child, offset, isOdd);
        }
    }

    offset -= Vector2(16.0f, 0.0f);
}

void Tree::Clear() {
    mRoot.Reset();
}

Ref<TreeItem> Tree::CreateItem(const Ref<TreeItem>& parent) {
    Ref<TreeItem> item = new TreeItem(this, parent);
    if (!mRoot) {
        mRoot = item;
    }
    return item;
}
