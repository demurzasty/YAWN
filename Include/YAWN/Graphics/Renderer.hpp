#pragma once 

#include "RendererDriver.hpp"
#include "../Threading/ExclusiveMutex.hpp"

namespace YAWN {
    class Renderer {
    public:
        static void Initialize();

        static void Release();

        static void SetCameraProjection(const Matrix4& projection);

        static void SetCameraTransform(const Matrix4& transform);

        static int CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount);

        static void DestroyTexture(int id);

        static bool IsTextureValid(int id);

        static int CreateInstance();

        static void DestroyInstance(int id);

        static bool IsInstanceValid(int id);

        static void SetInstanceTransform(int id, const Matrix4& transform);

        static void Present();

    private:
        static Ref<RendererDriver> sDriver;
        static ExclusiveMutex sMutex;
    };
}
