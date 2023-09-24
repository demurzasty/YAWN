#pragma once 

#include "../Node2D.hpp"
#include "../../Graphics/Color.hpp"
#include "../../Math/Rectangle.hpp"
#include "../../Graphics/Font.hpp"

namespace YAWN {
    class Control : public Node2D {
        YAWN_OBJECT(Control, Node2D);

    public:
        virtual void Enter() override;

        virtual void Draw() override;

        void SetLocalSize(const Vector2& size);

        const Vector2& GetLocalSize() const;

        void SetLocalRectangle(const Rectangle& rectangle);

        Rectangle GetLocalRectangle() const;

        Rectangle GetGlobalRectangle() const;

        void SetBackgroundColor(const Color4& color);

        const Color4& GetBackgroundColor() const;

    private:
        Vector2 mLocalSize = Vector2::Zero;
        Color4 mBackgroundColor = Color::Transparent;
        Ref<Font> mFont;
    };
}
