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

OID Renderer::CreateViewport(int width, int height, bool directToScreen) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->CreateViewport(width, height, directToScreen);
}

void Renderer::DestroyViewport(OID id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsViewportValid(id));

    sDriver->DestroyViewport(id);
}

bool Renderer::IsViewportValid(OID id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->IsViewportValid(id);
}

void Renderer::SetViewportSize(OID id, int width, int height) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsViewportValid(id));

    sDriver->SetViewportSize(id, width, height);
}

OID Renderer::GetViewportColorTexture(OID id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsViewportValid(id));

    return sDriver->GetViewportColorTexture(id);
}

OID Renderer::CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->CreateTexture(width, height, format, filter, wrapping, mipmapCount);
}

void Renderer::DestroyTexture(OID id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->DestroyTexture(id);
}

bool Renderer::IsTextureValid(OID id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->IsTextureValid(id);
}

void Renderer::SetTextureData(OID id, int mipmap, const void* data) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsTextureValid(id));

    sDriver->SetTextureData(id, mipmap, data);
}

Vector2 Renderer::GetTextureSize(OID id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsTextureValid(id));

    return sDriver->GetTextureSize(id);
}

OID Renderer::GetWhiteTexture() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->GetWhiteTexture();
}

OID Renderer::CreateMaterial() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->CreateMaterial();
}

void Renderer::DestroyMaterial(OID id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->DestroyMaterial(id);
}

bool Renderer::IsMaterialValid(OID id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->IsMaterialValid(id);
}

void Renderer::SetMaterialBaseColor(OID id, const Color4& color) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsMaterialValid(id));

    sDriver->SetMaterialBaseColor(id, color);
}

void Renderer::SetMaterialRoughness(OID id, float roughness) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsMaterialValid(id));

    sDriver->SetMaterialRoughness(id, roughness);
}

void Renderer::SetMaterialMetallic(OID id, float metallic) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsMaterialValid(id));

    sDriver->SetMaterialMetallic(id, metallic);
}

void Renderer::SetMaterialOcclusionStrength(OID id, float strength) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsMaterialValid(id));

    sDriver->SetMaterialOcclusionStrength(id, strength);
}

void Renderer::SetMaterialAlbedoTexture(OID id, OID textureId) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsMaterialValid(id));

    sDriver->SetMaterialAlbedoTexture(id, textureId);
}

void Renderer::SetMaterialNormalTexture(OID id, OID textureId) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsMaterialValid(id));

    sDriver->SetMaterialNormalTexture(id, textureId);
}

void Renderer::SetMaterialMetallicRoughnessTexture(OID id, OID textureId) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsMaterialValid(id));

    sDriver->SetMaterialMetallicRoughnessTexture(id, textureId);
}

void Renderer::SetMaterialEmissiveTexture(OID id, OID textureId) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsMaterialValid(id));

    sDriver->SetMaterialEmissiveTexture(id, textureId);
}

void Renderer::SetMaterialOcclusionTexture(OID id, OID textureId) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsMaterialValid(id));

    sDriver->SetMaterialOcclusionTexture(id, textureId);
}

OID Renderer::CreateMesh(int vertexCount, int indexCount) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->CreateMesh(vertexCount, indexCount);
}

void Renderer::DestroyMesh(OID id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->DestroyMesh(id);
}

bool Renderer::IsMeshValid(OID id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->IsMeshValid(id);
}

void Renderer::SetMeshData(OID id, const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsMeshValid(id));

    sDriver->SetMeshData(id, vertices, indices);
}

OID Renderer::CreateInstance() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->CreateInstance();
}

void Renderer::DestroyInstance(OID id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->DestroyInstance(id);
}

bool Renderer::IsInstanceValid(OID id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->IsInstanceValid(id);
}

void Renderer::SetInstanceTransform(OID id, const Matrix4& transform) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsInstanceValid(id));

    sDriver->SetInstanceTransform(id, transform);
}

void Renderer::SetInstanceMaterial(OID id, OID materialId) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsInstanceValid(id));
    YAWN_ASSERT(materialId == Pool::None || sDriver->IsMaterialValid(materialId));

    sDriver->SetInstanceMaterial(id, materialId);
}

void Renderer::SetInstanceMesh(OID id, OID meshId) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsInstanceValid(id));
    YAWN_ASSERT(meshId == Pool::None || sDriver->IsMeshValid(meshId));

    sDriver->SetInstanceMesh(id, meshId);
}

void Renderer::SetInstanceViewport(OID id, OID viewportId) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsInstanceValid(id));
    YAWN_ASSERT(viewportId == Pool::None || sDriver->IsViewportValid(viewportId));

    sDriver->SetInstanceViewport(id, viewportId);
}

OID Renderer::CreateCanvasItem() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->CreateCanvasItem();
}

void Renderer::DestroyCanvasItem(OID id) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->DestroyCanvasItem(id);
}

bool Renderer::IsCanvasItemValid(OID id) {
    ExclusiveLock lock(sMutex);

    return sDriver->IsCanvasItemValid(id);
}

void Renderer::SetCanvasItemData(OID id, const ArrayView<const Vertex2D>& vertices, const ArrayView<const int>& indices) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(sDriver->IsCanvasItemValid(id));

    sDriver->SetCanvasItemData(id, vertices, indices);
}

void Renderer::SetCanvasItemTexture(OID id, OID textureId) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);
    YAWN_ASSERT(IsCanvasItemValid(id));

    sDriver->SetCanvasItemTexture(id, textureId);
}

void Renderer::DrawCanvasItem(OID id, int vertexOffset, int indexOffset, int indexCount) {
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

void Renderer::LLSetTexture2D(OID textureId) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->LLSetTexture2D(textureId);
}

void Renderer::LLSetClipRect(const Rectangle& clipRect) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->LLSetClipRect(clipRect);
}

void Renderer::LLPushClipRect(const Rectangle& clipRect) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->LLPushClipRect(clipRect);
}

void Renderer::LLPopClipRect() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->LLPopClipRect();
}

void Renderer::LLDraw2D(Topology topology, int vertexOffset, int indexOffset, int indexCount) {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->LLDraw2D(topology, vertexOffset, indexOffset, indexCount);
}
