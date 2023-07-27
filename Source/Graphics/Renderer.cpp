#include <YAWN/Graphics/Renderer.hpp>

#include "../Drivers/OpenGL/RendererDriverOpenGL.hpp"

using namespace YAWN;

Ref<RendererDriver> Renderer::sDriver;
ExclusiveMutex Renderer::sMutex;

void Renderer::Initialize() {
    ExclusiveLock lock(sMutex);

    sDriver = new RendererDriverOpenGL();
}

void Renderer::SetCameraProjection(const Matrix4& projection) {
    ExclusiveLock lock(sMutex);

    sDriver->SetCameraProjection(projection);
}

void Renderer::SetCameraTransform(const Matrix4& transform) {
    ExclusiveLock lock(sMutex);

    sDriver->SetCameraTransform(transform);
}

int Renderer::CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount) {
    ExclusiveLock lock(sMutex);

    return sDriver->CreateTexture(width, height, format, filter, wrapping, mipmapCount);
}

void Renderer::DestroyTexture(int id) {
    ExclusiveLock lock(sMutex);

    sDriver->DestroyTexture(id);
}

bool Renderer::IsTextureValid(int id) {
    ExclusiveLock lock(sMutex);

    return sDriver->IsTextureValid(id);
}

int Renderer::CreateInstance() {
    ExclusiveLock lock(sMutex);

    return sDriver->CreateInstance();
}

void Renderer::DestroyInstance(int id) {
    ExclusiveLock lock(sMutex);

    sDriver->DestroyInstance(id);
}

bool Renderer::IsInstanceValid(int id) {
    ExclusiveLock lock(sMutex);

    return sDriver->IsInstanceValid(id);
}

void Renderer::SetInstanceTransform(int id, const Matrix4& transform) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(IsInstanceValid(id));

    sDriver->SetInstanceTransform(id, transform);
}

void Renderer::Release() {
    ExclusiveLock lock(sMutex);

    sDriver.Reset();
}

void Renderer::Present() {
    ExclusiveLock lock(sMutex);

    sDriver->Present();
}
