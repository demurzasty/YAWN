#pragma once 

#include "Control.hpp"

namespace YAWN {
    class Tree;

    class TreeItem : public Reference {
    public:
        TreeItem(Tree* tree, const Ref<TreeItem>& parent);

        void SetText(const String& text);

        const String& GetText() const;

        void SetGlobalRectangle(const Rectangle& rectangle);

        const Rectangle& GetGlobalRectangle() const;

        const Array<Ref<TreeItem>>& GetChildren() const;

        void SetCollapsed(bool collapsed);

        bool IsCollapsed() const;

    public:
        Tree* mTree;
        Array<Ref<TreeItem>> mChildren;
        String mText;
        Rectangle mRectangle = Rectangle(0.0f, 0.0f, 0.0f, 0.0f);
        bool mCollapsed = false;
    };

    class Tree : public Control {
        YAWN_OBJECT(Tree, Control);

        friend class TreeItem;

    public:
        virtual ~Tree() = default;

        virtual void HandleEvent(const Event& event) override;

        virtual void Draw() override;

        void Clear();

        Ref<TreeItem> CreateItem(const Ref<TreeItem>& parent = nullptr);

    private:
        void HandleEvent(const Event& event, const Ref<TreeItem>& item, Vector2& offset);

        void Update(float timeStep, const Ref<TreeItem>& item, Vector2& offset);

        void Draw(const Ref<Theme>& theme, const Ref<TreeItem>& item, Vector2& offset, bool& isOdd);

    private:
        Ref<TreeItem> mRoot;
    };
}
