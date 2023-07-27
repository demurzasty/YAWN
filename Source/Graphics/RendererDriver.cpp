#include <YAWN/Graphics/RendererDriver.hpp>

using namespace YAWN;

int RendererDriver::CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount) {
    return mTexturePool.Acquire();
}

void RendererDriver::DestroyTexture(int id) {
    mTexturePool.Dispose(id);
}

bool RendererDriver::IsTextureValid(int id) {
    return mTexturePool.IsValid(id);
}

int RendererDriver::CreateInstance() {
    return mInstancePool.Acquire();
}

void RendererDriver::DestroyInstance(int id) {
    mInstancePool.Dispose(id);
}

bool RendererDriver::IsInstanceValid(int id) {
    return mInstancePool.IsValid(id);
}
