#pragma once 

#include "RendererDriver.hpp"
#include "../Threading/ExclusiveMutex.hpp"

namespace YAWN {
    class Renderer {
    public:
        static void Initialize();

        static void Release();

        static void SetFramebufferSize(const Vector2& size);

        static void SetClearColor(const Color& color);

        static void SetCameraProjection(const Matrix4& projection);

        static void SetCameraTransform(const Matrix4& transform);

        static OID CreateViewport(int width, int height, bool directToScreen);

        static void DestroyViewport(OID id);

        static bool IsViewportValid(OID id);

        static void SetViewportSize(OID id, int width, int height);

        static OID GetViewportColorTexture(OID id);

        static OID CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount);

        static void DestroyTexture(OID id);

        static bool IsTextureValid(OID id);

        static void SetTextureData(OID id, int mipmap, const void* data);

        static Vector2 GetTextureSize(OID id);

        static OID GetWhiteTexture();

        static OID CreateMaterial();

        static void DestroyMaterial(OID id);

        static bool IsMaterialValid(OID id);

        static void SetMaterialBaseColor(OID id, const Color4& color);

        static void SetMaterialRoughness(OID id, float roughness);

        static void SetMaterialMetallic(OID id, float metallic);

        static void SetMaterialOcclusionStrength(OID id, float strength);

        static void SetMaterialAlbedoTexture(OID id, OID textureId);

        static void SetMaterialNormalTexture(OID id, OID textureId);

        static void SetMaterialMetallicRoughnessTexture(OID id, OID textureId);

        static void SetMaterialEmissiveTexture(OID id, OID textureId);

        static void SetMaterialOcclusionTexture(OID id, OID textureId);

        static OID CreateMesh(int vertexCount, int indexCount);

        static void DestroyMesh(OID id);

        static bool IsMeshValid(OID id);

        static void SetMeshData(OID id, const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices);

        static OID CreateInstance();

        static void DestroyInstance(OID id);

        static bool IsInstanceValid(OID id);

        static void SetInstanceTransform(OID id, const Matrix4& transform);

        static void SetInstanceMaterial(OID id, OID materialId);

        static void SetInstanceMesh(OID id, OID meshId);

        static void SetInstanceViewport(OID id, OID viewportId);

        static OID CreateCanvasItem();

        static void DestroyCanvasItem(OID id);

        static bool IsCanvasItemValid(OID id);

        static void SetCanvasItemData(OID id, const ArrayView<const Vertex2D>& vertices, const ArrayView<const int>& indices);

        static void SetCanvasItemTexture(OID id, OID textureId);

        static void DrawCanvasItem(OID id, int vertexOffset, int indexOffset, int indexCount);

        static void Render();

    public:
        static void LLSetVertexBufferData2D(const ArrayView<const Vertex2D>& vertices);

        static void LLSetIndexBufferData2D(const ArrayView<const unsigned short>& indices);

        static void LLSetTexture2D(OID textureId);

        static void LLSetClipRect(const Rectangle& clipRect);

        static void LLPushClipRect(const Rectangle& clipRect);

        static void LLPopClipRect();

        static void LLDraw2D(Topology topology, int vertexOffset, int indexOffset, int indexCount);

    private:
        static Ref<RendererDriver> sDriver;
        static ExclusiveMutex sMutex;
    };
}
