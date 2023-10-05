#include <YAWN/Scene/UI/TextureRect.hpp>

using namespace YAWN;

void TextureRect::Draw() {
    Base::Draw();

    if (GetTexture()) {
        DrawTexture(GetTexture()->GetId(), GetGlobalRectangle(), Rectangle(Vector2::Zero, GetTexture()->GetSize()), Color::White);
    }
}

void TextureRect::SetTexture(const Ref<Texture>& texture) {
    mTexture = texture;
}

const Ref<Texture>& TextureRect::GetTexture() const {
    return mTexture;
}

