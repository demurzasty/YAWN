#include "GraphicsDeviceDriverOpenGL.hpp"
#include "BufferOpenGL.hpp"
#include "TextureOpenGL.hpp"

using namespace YAWN;

GraphicsDeviceDriverOpenGL::GraphicsDeviceDriverOpenGL() {
}

GraphicsDeviceDriverOpenGL::~GraphicsDeviceDriverOpenGL() {
}

Ref<Buffer> GraphicsDeviceDriverOpenGL::CreateBuffer(int elementSize, int elementCount, const void* data, int flags) {
    return new BufferOpenGL(elementSize, elementCount, data, flags);
}

Ref<Texture> GraphicsDeviceDriverOpenGL::CreateTexture(int width, int height, int depth, int levels, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int flags) {
    return new TextureOpenGL(width, height, depth, levels, format, filter, wrapping, flags);
}

void GraphicsDeviceDriverOpenGL::SetViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}
