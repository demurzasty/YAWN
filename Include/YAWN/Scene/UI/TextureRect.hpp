#pragma once 

#include "Control.hpp"

namespace YAWN {
    class TextureRect : public Control {
        YAWN_OBJECT(TextureRect, Control);

    public:
        virtual ~TextureRect() = default;

        virtual void Draw() override;

        void SetTexture(const Ref<Texture>& texture);

        const Ref<Texture>& GetTexture() const;

    private:
        Ref<Texture> mTexture;
    };
}