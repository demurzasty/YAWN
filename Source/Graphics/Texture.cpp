#include <YAWN/Graphics/Texture.hpp>
#include <YAWN/Graphics/Renderer.hpp>

using namespace YAWN;

void Texture::Register(Meta<Texture>& meta) {
    meta.SetName(L"Texture");
    meta.SetBase<Resource>();
}

Texture::Texture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount)
    : mId(Renderer::CreateTexture(width, height, format, filter, wrapping, mipmapCount)) {
}

Texture::~Texture() {
    Renderer::DestroyTexture(mId);
}

void Texture::SetData(int mipmap, const void* data) {
    Renderer::SetTextureData(mId, mipmap, data);
}

Vector2 Texture::GetSize() const {
    return Renderer::GetTextureSize(mId);
}

int Texture::GetId() const {
    return mId;
}
