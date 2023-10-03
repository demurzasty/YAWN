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

        static int CreateViewport(int width, int height, bool directToScreen);

        static void DestroyViewport(int id);

        static bool IsViewportValid(int id);

        static void SetViewportSize(int id, int width, int height);

        static int GetViewportColorTexture(int id);

        static int CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount);

        static void DestroyTexture(int id);

        static bool IsTextureValid(int id);

        static void SetTextureData(int id, int mipmap, const void* data);

        static Vector2 GetTextureSize(int id);

        static int GetWhiteTexture();

        static int CreateMaterial();

        static void DestroyMaterial(int id);

        static bool IsMaterialValid(int id);

        static void SetMaterialBaseColor(int id, const Color4& color);

        static void SetMaterialRoughness(int id, float roughness);

        static void SetMaterialMetallic(int id, float metallic);

        static void SetMaterialOcclusionStrength(int id, float strength);

        static void SetMaterialAlbedoTexture(int id, int textureId);

        static void SetMaterialNormalTexture(int id, int textureId);

        static void SetMaterialMetallicRoughnessTexture(int id, int textureId);

        static void SetMaterialEmissiveTexture(int id, int textureId);

        static void SetMaterialOcclusionTexture(int id, int textureId);

        static int CreateMesh(int vertexCount, int indexCount);

        static void DestroyMesh(int id);

        static bool IsMeshValid(int id);

        static void SetMeshData(int id, const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices);

        static int CreateInstance();

        static void DestroyInstance(int id);

        static bool IsInstanceValid(int id);

        static void SetInstanceTransform(int id, const Matrix4& transform);

        static void SetInstanceMaterial(int id, int materialId);

        static void SetInstanceMesh(int id, int meshId);

        static void SetInstanceViewport(int id, int viewportId);

        static int CreateCanvasItem();

        static void DestroyCanvasItem(int id);

        static bool IsCanvasItemValid(int id);

        static void SetCanvasItemData(int id, const ArrayView<const Vertex2D>& vertices, const ArrayView<const int>& indices);

        static void SetCanvasItemTexture(int id, int textureId);

        static void DrawCanvasItem(int id, int vertexOffset, int indexOffset, int indexCount);

        static void Render();

    public:
        static void LLSetVertexBufferData2D(const ArrayView<const Vertex2D>& vertices);

        static void LLSetIndexBufferData2D(const ArrayView<const unsigned short>& indices);

        static void LLSetTexture2D(int textureId);

        static void LLSetClipRect(const Rectangle& clipRect);

        static void LLPushClipRect(const Rectangle& clipRect);

        static void LLPopClipRect();

        static void LLDraw2D(Topology topology, int vertexOffset, int indexOffset, int indexCount);

    private:
        static Ref<RendererDriver> sDriver;
        static ExclusiveMutex sMutex;
    };
}
