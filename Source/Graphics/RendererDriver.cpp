#include <YAWN/Graphics/RendererDriver.hpp>

using namespace YAWN;

void RendererDriver::SetClearColor(const Color& color) {
    mClearColor = color;
}

int RendererDriver::CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount) {
    return mTexturePool.Acquire();
}

void RendererDriver::DestroyTexture(int id) {
    mTexturePool.Dispose(id);
}

bool RendererDriver::IsTextureValid(int id) {
    return mTexturePool.IsValid(id);
}

int RendererDriver::CreateMesh(int vertexCount, int indexCount) {
    return mMeshPool.Acquire();
}

void RendererDriver::DestroyMesh(int id) {
    mMeshPool.Dispose(id);
}

bool RendererDriver::IsMeshValid(int id) {
    return mMeshPool.IsValid(id);
}

void RendererDriver::SetMeshData(int id, const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices) {
    // TODO: What should I do?
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
