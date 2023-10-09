#include <YAWN/Graphics/RendererDriver.hpp>
#include <YAWN/Platform/Window.hpp>

using namespace YAWN;

void RendererDriver::SetClearColor(const Color& color) {
    mClearColor = color;
}

OID RendererDriver::CreateViewport(int width, int height, bool directToScreen) {
    return mViewportPool.Acquire();
}

void RendererDriver::DestroyViewport(OID id) {
    mViewportPool.Dispose(id);
}

bool RendererDriver::IsViewportValid(OID id) {
    return mViewportPool.IsValid(id);
}

OID RendererDriver::CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount) {
    return mTexturePool.Acquire();
}

void RendererDriver::DestroyTexture(OID id) {
    mTexturePool.Dispose(id);
}

bool RendererDriver::IsTextureValid(OID id) {
    return mTexturePool.IsValid(id);
}

OID RendererDriver::CreateMaterial() {
    return mMaterialPool.Acquire();
}

void RendererDriver::DestroyMaterial(OID id) {
    mMaterialPool.Dispose(id);
}

bool RendererDriver::IsMaterialValid(OID id) {
    return mMaterialPool.IsValid(id);
}

OID RendererDriver::CreateMesh(int vertexCount, int indexCount) {
    return mMeshPool.Acquire();
}

void RendererDriver::DestroyMesh(OID id) {
    mMeshPool.Dispose(id);
}

bool RendererDriver::IsMeshValid(OID id) {
    return mMeshPool.IsValid(id);
}

OID RendererDriver::CreateInstance() {
    return mInstancePool.Acquire();
}

void RendererDriver::DestroyInstance(OID id) {
    mInstancePool.Dispose(id);
}

bool RendererDriver::IsInstanceValid(OID id) {
    return mInstancePool.IsValid(id);
}

OID RendererDriver::CreateCanvasItem() {
    return mCanvasItemPool.Acquire();
}

void RendererDriver::DestroyCanvasItem(OID id) {
    mCanvasItemPool.Dispose(id);
}

bool RendererDriver::IsCanvasItemValid(OID id) {
    return mCanvasItemPool.IsValid(id);
}

void RendererDriver::LLPushClipRect(const Rectangle& clipRect) {
    if (!mClipRects.IsEmpty()) {
        Rectangle newClipRect = Rectangle::Intersect(clipRect, mClipRects.GetBack());

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
