#include <YAWN/Graphics/Renderer.hpp>

#include "../Drivers/OpenGL/RendererDriverOpenGL.hpp"

using namespace YAWN;

Ref<RendererDriver> Renderer::sDriver;
ExclusiveMutex Renderer::sMutex;

void Renderer::Initialize() {
    ExclusiveLock lock(sMutex);

    sDriver = new RendererDriverOpenGL();
}

void Renderer::SetClearColor(const Color& color) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->SetClearColor(color);
}

void Renderer::SetCameraProjection(const Matrix4& projection) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->SetCameraProjection(projection);
}

void Renderer::SetCameraTransform(const Matrix4& transform) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->SetCameraTransform(transform);
}

int Renderer::CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->CreateTexture(width, height, format, filter, wrapping, mipmapCount);
}

void Renderer::DestroyTexture(int id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->DestroyTexture(id);
}

bool Renderer::IsTextureValid(int id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->IsTextureValid(id);
}

int Renderer::CreateMesh(int vertexCount, int indexCount) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->CreateMesh(vertexCount, indexCount);
}

void Renderer::DestroyMesh(int id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->DestroyMesh(id);
}

bool Renderer::IsMeshValid(int id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->IsMeshValid(id);
}

void Renderer::SetMeshData(int id, const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->SetMeshData(id, vertices, indices);
}

int Renderer::CreateInstance() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->CreateInstance();
}

void Renderer::DestroyInstance(int id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->DestroyInstance(id);
}

bool Renderer::IsInstanceValid(int id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->IsInstanceValid(id);
}

void Renderer::SetInstanceTransform(int id, const Matrix4& transform) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    YAWN_ASSERT(IsInstanceValid(id));

    sDriver->SetInstanceTransform(id, transform);
}

void Renderer::Draw2D(Topology topology, const ArrayView<const Vertex2D>& vertices, const ArrayView<const int>& indices) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->Draw2D(topology, vertices, indices);
}

void Renderer::Release() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver.Reset();
}

void Renderer::Present() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->Present();
}
