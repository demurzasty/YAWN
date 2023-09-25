#pragma once 

#include "Font.hpp"
#include "Color.hpp"

namespace YAWN {
    class Theme : public Resource {
        YAWN_OBJECT(Theme, Resource);

    public:
        static Ref<Theme> CreateDefault();

        virtual ~Theme() = default;

        void SetDefaultFont(const Ref<Font>& font);

        const Ref<Font>& GetDefaultFont() const;

        void SetContainerColor(const Color4& color);

        const Color4& GetContainerColor() const;

        void SetButtonDefaultColor(const Color4& color);

        const Color4& GetButtonDefaultColor() const;

        void SetButtonHoverColor(const Color4& color);

        const Color4& GetButtonHoverColor() const;

        void SetButtonActiveColor(const Color4& color);

        const Color4& GetButtonActiveColor() const;

        void SetButtonTextColor(const Color4& color);

        const Color4& GetButtonTextColor() const;

        void SetSplitterColor(const Color4& color);

        const Color4& GetSplitterColor() const;

        void SetActiveSplitterColor(const Color4& color);

        const Color4& GetActiveSplitterColor() const;

        void SetSectionIndicatorColor(const Color4& color);

        const Color4& GetSectionIndicatorColor() const;

        void SetSectionBarColor(const Color4& color);

        const Color4& GetSectionBarColor() const;

        void SetFrameBorderColor(const Color4& color);

        const Color4& GetFrameBorderColor() const;

    private:
        Ref<Font> mDefaultFont;
        Color4 mContainerColor = Color4(54, 54, 54);
        Color4 mButtonDefaultColor = Color4(54, 54, 54);
        Color4 mButtonHoverColor = Color4(86, 86, 86);
        Color4 mButtonActiveColor = Color4(42, 42, 42);
        Color4 mButtonTextColor = Color4(255, 255, 255);
        Color4 mSplitterColor = Color4(42, 42, 42);
        Color4 mActiveSplitterColor = Color4(64, 64, 64);
        Color4 mSectionIndicatorColor = Color4(243, 95, 85);
        Color4 mSectionBarColor = Color4(42, 42, 42);
        Color4 mFrameBorderColor = Color4(86, 86, 86);
    };
}
