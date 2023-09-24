#pragma once 

#include "../Runtime/Resource.hpp"
#include "../Core/ArrayView.hpp"
#include "../Graphics/Color.hpp"
#include "../Math/Rectangle.hpp"
#include "../Core/Map.hpp"
#include "../Core/String.hpp"

namespace YAWN {
    struct FontGlyph {
        float Advance = 0.0f;
        Rectangle Rectangle = YAWN::Rectangle(0.0f, 0.0f, 0.0f, 0.0f);
        Vector2 Offset = Vector2::Zero;
    };

    class Font : public Resource {
        YAWN_OBJECT(Font, Resource);

    public:
        Font(const ArrayView<const unsigned char>& data);

        virtual ~Font() override;

        const FontGlyph& GetGlyph(int codepoint, int size) const;

        float GetKerning(int codepoint1, int codepoint2, int size) const;

        Vector2 GetTextSize(const String& text, int size) const;

    private:
        Rectangle Pack(const Vector2& size) const;

    private:
        struct InternalData;

    private:
        const int mId;
        mutable Array<unsigned char> mData;
        mutable InternalData* mInternalData;
        mutable Array<Color4> mPixels;
        mutable Map<int, FontGlyph> mGlyphs;
    };
}
