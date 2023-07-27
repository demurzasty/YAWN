#include <YAWN/Graphics/Texture.hpp>
#include <YAWN/Graphics/Renderer.hpp>

using namespace YAWN;

Texture::Texture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount)
    : mId(Renderer::CreateTexture(width, height, format, filter, wrapping, mipmapCount)) {
}

Texture::~Texture() {
    Renderer::DestroyTexture(mId);
}
