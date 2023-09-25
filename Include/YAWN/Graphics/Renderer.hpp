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

        static int CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount);

        static void DestroyTexture(int id);

        static bool IsTextureValid(int id);

        static void SetTextureData(int id, int mipmap, const void* data);

        static Vector2 GetTextureSize(int id);

        static int GetWhiteTexture();

        static int CreateMesh(int vertexCount, int indexCount);

        static void DestroyMesh(int id);

        static bool IsMeshValid(int id);

        static void SetMeshData(int id, const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices);

        static int CreateInstance();

        static void DestroyInstance(int id);

        static bool IsInstanceValid(int id);

        static void SetInstanceTransform(int id, const Matrix4& transform);

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

        static void LLDraw2D(Topology topology, int vertexOffset, int indexOffset, int indexCount);

    private:
        static Ref<RendererDriver> sDriver;
        static ExclusiveMutex sMutex;
    };
}
