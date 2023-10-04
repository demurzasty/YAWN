#pragma once 

#include "../Node2D.hpp"
#include "../../Graphics/Color.hpp"
#include "../../Math/Rectangle.hpp"
#include "../../Graphics/Theme.hpp"
#include "../../Math/Vector4.hpp"

namespace YAWN {
    class Control : public Node2D {
        YAWN_OBJECT(Control, Node2D);

    public:
        Control();

        virtual ~Control() = default;

        virtual void Enter() override;

        virtual void Update(float timeStep) override;

        virtual void Draw() override;

        void SetLocalSize(const Vector2& size);

        const Vector2& GetLocalSize() const;

        void SetMinimumSize(const Vector2& size);

        const Vector2& GetMinimumSize() const;

        void SetLocalRectangle(const Rectangle& rectangle);

        Rectangle GetLocalRectangle() const;

        Rectangle GetGlobalRectangle() const;

        Rectangle GetGlobalClientRectangle() const;

        Control* GetControlParent() const;

        void SetTheme(const Ref<Theme>& theme);

        const Ref<Theme>& GetTheme() const;

        void SetHorizontalExpand(bool expand);

        bool IsHorizontalExpand() const;

        void SetVerticalExpand(bool expand);

        bool IsVerticalExpand() const;

        void SetPadding(const Vector4& padding);

        const Vector4& GetPadding() const;

        void GrabFocus();

        void LoseFocus();

        bool HasFocus() const;

    protected:
        virtual void OnReparent() override;

    private:
        Vector2 mLocalSize = Vector2::Zero;
        Vector2 mMinimumSize = Vector2::Zero;
        Control* mControlParent = nullptr;
        Ref<Theme> mTheme;
        bool mHorizontalExpand = false;
        bool mVerticalExpand = false;
        Vector4 mPadding = 0.0f;
    };
}
