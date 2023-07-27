#include <YAWN/RHI/GraphicsDevice.hpp>

#include "../Drivers/OpenGL/GraphicsDeviceDriverOpenGL.hpp"

using namespace YAWN;

Ref<GraphicsDeviceDriver> GraphicsDevice::sDriver;
ExclusiveMutex GraphicsDevice::sMutex;

void GraphicsDevice::Initialize() {
	sDriver = new GraphicsDeviceDriverOpenGL();
}

void GraphicsDevice::Release() {
	sDriver.Reset();
}

Ref<Buffer> GraphicsDevice::CreateBuffer(int elementSize, int elementCount, const void* data, int flags) {
	ExclusiveLock lock(sMutex);

	return sDriver->CreateBuffer(elementSize, elementCount, data, flags);
}

Ref<BufferView> GraphicsDevice::CreateBufferView(Ref<Buffer> buffer, int elementOffset, int elementCount) {
	ExclusiveLock lock(sMutex);

	return new BufferView(buffer, elementOffset, elementCount);
}

Ref<Texture> GraphicsDevice::CreateTexture(int width, int height, int depth, int levels, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int flags) {
	ExclusiveLock lock(sMutex);

	return sDriver->CreateTexture(width, height, depth, levels, format, filter, wrapping, flags);
}

void GraphicsDevice::SetViewport(int x, int y, int width, int height) {
	ExclusiveLock lock(sMutex);

	sDriver->SetViewport(x, y, width, height);
}
