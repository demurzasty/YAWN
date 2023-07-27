#pragma once 

#include "Buffer.hpp"
#include "BufferView.hpp"
#include "Texture.hpp"

namespace YAWN {
    class GraphicsDeviceDriver : public Reference {
        YAWN_OBJECT(GraphicsDeviceDriver, Reference);

    public:
        virtual ~GraphicsDeviceDriver() = default;

        virtual Ref<Buffer> CreateBuffer(int elementSize, int elementCount, const void* data, int flags) = 0;

        virtual Ref<Texture> CreateTexture(int width, int height, int depth, int levels, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int flags) = 0;

        virtual void SetViewport(int x, int y, int width, int height) = 0;
    };
}
