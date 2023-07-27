#pragma once 

#include <YAWN/RHI/GraphicsDeviceDriver.hpp>

#include <GL/glew.h>

namespace YAWN {
    class GraphicsDeviceDriverOpenGL : public GraphicsDeviceDriver {
        YAWN_OBJECT(GraphicsDeviceDriverOpenGL, GraphicsDeviceDriver);

    public:
        GraphicsDeviceDriverOpenGL();

        ~GraphicsDeviceDriverOpenGL();

        Ref<Buffer> CreateBuffer(int elementSize, int elementCount, const void* data, int flags) override;

        Ref<Texture> CreateTexture(int width, int height, int depth, int levels, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int flags) override;

        void SetViewport(int x, int y, int width, int height) override;
    };
}
