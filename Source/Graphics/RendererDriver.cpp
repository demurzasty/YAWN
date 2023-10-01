#include <YAWN/Graphics/RendererDriver.hpp>
#include <YAWN/Platform/Window.hpp>

using namespace YAWN;

void RendererDriver::SetClearColor(const Color& color) {
    mClearColor = color;
}

int RendererDriver::CreateViewport(int width, int height) {
    return mViewportPool.Acquire();
}

void RendererDriver::DestroyViewport(int id) {
    mViewportPool.Dispose(id);
}

bool RendererDriver::IsViewportValid(int id) {
    return mViewportPool.IsValid(id);
}

int RendererDriver::CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount) {
    return mTexturePool.Acquire();
}

void RendererDriver::DestroyTexture(int id) {
    mTexturePool.Dispose(id);
}

bool RendererDriver::IsTextureValid(int id) {
    return mTexturePool.IsValid(id);
}

int RendererDriver::CreateMesh(int vertexCount, int indexCount) {
    return mMeshPool.Acquire();
}

void RendererDriver::DestroyMesh(int id) {
    mMeshPool.Dispose(id);
}

bool RendererDriver::IsMeshValid(int id) {
    return mMeshPool.IsValid(id);
}

int RendererDriver::CreateInstance() {
    return mInstancePool.Acquire();
}

void RendererDriver::DestroyInstance(int id) {
    mInstancePool.Dispose(id);
}

bool RendererDriver::IsInstanceValid(int id) {
    return mInstancePool.IsValid(id);
}

int RendererDriver::CreateCanvasItem() {
    return mCanvasItemPool.Acquire();
}

void RendererDriver::DestroyCanvasItem(int id) {
    mCanvasItemPool.Dispose(id);
}

bool RendererDriver::IsCanvasItemValid(int id) {
    return mCanvasItemPool.IsValid(id);
}

void RendererDriver::LLPushClipRect(const Rectangle& clipRect) {
    if (!mClipRects.IsEmpty()) {
        Rectangle newClipRect = clipRect.Intersect(mClipRects.GetBack());

        LLSetClipRect(newClipRect);

        mClipRects.Add(newClipRect);
    } else {
        LLSetClipRect(clipRect);

        mClipRects.Add(clipRect);
    }
}

void RendererDriver::LLPopClipRect() {
    if (!mClipRects.IsEmpty()) {
        mClipRects.Pop();

        if (!mClipRects.IsEmpty()) {
            LLSetClipRect(mClipRects.GetBack());
        } else {
            LLSetClipRect(Rectangle(Vector2::Zero, Window::GetSize()));
        }
    } 
}
