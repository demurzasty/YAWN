#include <YAWN/Graphics/Renderer.hpp>

#include "../Drivers/OpenGL/RendererDriverOpenGL.hpp"

using namespace YAWN;

Ref<RendererDriver> Renderer::sDriver;
ExclusiveMutex Renderer::sMutex;

void Renderer::Initialize() {
    ExclusiveLock lock(sMutex);

    sDriver = new RendererDriverOpenGL();
}

void Renderer::SetFramebufferSize(const Vector2& size) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->SetFramebufferSize(size);
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

void Renderer::SetTextureData(int id, int mipmap, const void* data) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsTextureValid(id));

    return sDriver->SetTextureData(id, mipmap, data);
}

int Renderer::GetWhiteTexture() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->GetWhiteTexture();
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
    YAWN_ASSERT(sDriver->IsInstanceValid(id));

    sDriver->SetInstanceTransform(id, transform);
}

int Renderer::CreateCanvasItem() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->CreateCanvasItem();
}

void Renderer::DestroyCanvasItem(int id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->DestroyCanvasItem(id);
}

bool Renderer::IsCanvasItemValid(int id) {
    ExclusiveLock lock(sMutex);

    return sDriver->IsCanvasItemValid(id);
}

void Renderer::SetCanvasItemData(int id, const ArrayView<const Vertex2D>& vertices, const ArrayView<const int>& indices) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsCanvasItemValid(id));

    sDriver->SetCanvasItemData(id, vertices, indices);
}

void Renderer::SetCanvasItemTexture(int id, int textureId) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(IsCanvasItemValid(id));

    sDriver->SetCanvasItemTexture(id, textureId);
}

void Renderer::DrawCanvasItem(int id, int vertexOffset, int indexOffset, int indexCount) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(IsCanvasItemValid(id));

    sDriver->DrawCanvasItem(id, vertexOffset, indexOffset, indexCount);
}

void Renderer::Release() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver.Reset();
}

void Renderer::Render() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->Render();
}

void Renderer::LLSetVertexBufferData2D(const ArrayView<const Vertex2D>& vertices) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->LLSetVertexBufferData2D(vertices);
}

void Renderer::LLSetIndexBufferData2D(const ArrayView<const unsigned short>& indices) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->LLSetIndexBufferData2D(indices);
}

void Renderer::LLSetTexture2D(int textureId) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->LLSetTexture2D(textureId);
}

void Renderer::LLSetClipRect(const Vector4& clipRect) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->LLSetClipRect(clipRect);
}

void Renderer::LLDraw2D(int vertexOffset, int indexOffset, int indexCount) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->LLDraw2D(vertexOffset, indexOffset, indexCount);
}
