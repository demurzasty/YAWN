#pragma once 

#include "RendererDriver.hpp"
#include "../Threading/ExclusiveMutex.hpp"

namespace YAWN {
    class Renderer {
    public:
        static void Initialize();

        static void Release();

        static void SetClearColor(const Color& color);

        static void SetCameraProjection(const Matrix4& projection);

        static void SetCameraTransform(const Matrix4& transform);

        static int CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount);

        static void DestroyTexture(int id);

        static bool IsTextureValid(int id);

        static int CreateMesh(int vertexCount, int indexCount);

        static void DestroyMesh(int id);

        static bool IsMeshValid(int id);

        static void SetMeshData(int id, const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices);

        static int CreateInstance();

        static void DestroyInstance(int id);

        static bool IsInstanceValid(int id);

        static void SetInstanceTransform(int id, const Matrix4& transform);

        static void Draw2D(Topology topology, const ArrayView<const Vertex2D>& vertices, const ArrayView<const int>& indices);

        static void Present();

    private:
        static Ref<RendererDriver> sDriver;
        static ExclusiveMutex sMutex;
    };
}
