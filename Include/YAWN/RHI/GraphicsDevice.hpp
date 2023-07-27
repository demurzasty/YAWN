#pragma once 

#include "GraphicsDeviceDriver.hpp"
#include "../Threading/ExclusiveMutex.hpp"

namespace YAWN {
    class GraphicsDevice {
    public:
        static void Initialize();

        static void Release();

        static Ref<Buffer> CreateBuffer(int elementSize, int elementCount, const void* data, int flags);

        static Ref<BufferView> CreateBufferView(Ref<Buffer> buffer, int elementOffset, int elementCount);

        static Ref<Texture> CreateTexture(int width, int height, int depth, int levels, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int flags);

        static void SetViewport(int x, int y, int width, int height);

    private:
        static Ref<GraphicsDeviceDriver> sDriver;
        static ExclusiveMutex sMutex;
    };
}
