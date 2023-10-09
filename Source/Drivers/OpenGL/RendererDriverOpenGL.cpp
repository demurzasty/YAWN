#include "RendererDriverOpenGL.hpp"

#include <YAWN/Platform/Window.hpp>
#include <YAWN/Runtime/Console.hpp>

#include "Shaders/Generated/Culling.comp.h"
#include "Shaders/Generated/Forward.vert.h"
#include "Shaders/Generated/Forward.frag.h"
#include "Shaders/Generated/Canvas.vert.h"
#include "Shaders/Generated/Canvas.frag.h"

#include <stddef.h> // offsetof

using namespace YAWN;

RendererDriverOpenGL::RendererDriverOpenGL() {
    YAWN_GL_CHECK(glCreateBuffers(1, &mGlobalBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mGlobalBufferId, sizeof(GPUGlobalData), nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT));

    YAWN_GL_CHECK(glCreateBuffers(1, &mInstanceBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mInstanceBufferId, sizeof(GPUInstanceData) * MaxInstanceCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT));

    YAWN_GL_CHECK(glCreateBuffers(1, &mMaterialBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mMaterialBufferId, sizeof(GPUMaterialData) * MaxMaterialCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT));

    YAWN_GL_CHECK(glCreateBuffers(1, &mMeshBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mMeshBufferId, sizeof(GPUMeshData) * MaxMeshCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT));

    YAWN_GL_CHECK(glCreateBuffers(1, &mSamplerBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mSamplerBufferId, sizeof(GLuint64) * MaxTextureCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT));

    YAWN_GL_CHECK(glCreateBuffers(1, &mDrawBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mDrawBufferId, sizeof(GPUDrawElementsIndirectCommand) * MaxInstanceCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT));

    YAWN_GL_CHECK(glCreateBuffers(1, &mVertexBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mVertexBufferId, sizeof(Vertex3D) * MaxVertexCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT));

    YAWN_GL_CHECK(glCreateBuffers(1, &mIndexBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mIndexBufferId, sizeof(unsigned int) * MaxIndexCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT));

    YAWN_GL_CHECK(glCreateVertexArrays(1, &mVertexArrayObjectId));

    YAWN_GL_CHECK(glVertexArrayVertexBuffer(mVertexArrayObjectId, 0, mVertexBufferId, 0, sizeof(Vertex3D)));
    YAWN_GL_CHECK(glVertexArrayElementBuffer(mVertexArrayObjectId, mIndexBufferId));

    YAWN_GL_CHECK(glEnableVertexArrayAttrib(mVertexArrayObjectId, 0));
    YAWN_GL_CHECK(glEnableVertexArrayAttrib(mVertexArrayObjectId, 1));
    YAWN_GL_CHECK(glEnableVertexArrayAttrib(mVertexArrayObjectId, 2));

    YAWN_GL_CHECK(glVertexArrayAttribFormat(mVertexArrayObjectId, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex3D, Position)));
    YAWN_GL_CHECK(glVertexArrayAttribFormat(mVertexArrayObjectId, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex3D, UV)));
    YAWN_GL_CHECK(glVertexArrayAttribFormat(mVertexArrayObjectId, 2, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex3D, Normal)));

    YAWN_GL_CHECK(glVertexArrayAttribBinding(mVertexArrayObjectId, 0, 0));
    YAWN_GL_CHECK(glVertexArrayAttribBinding(mVertexArrayObjectId, 1, 0));
    YAWN_GL_CHECK(glVertexArrayAttribBinding(mVertexArrayObjectId, 2, 0));

    YAWN_GL_CHECK(glCreateBuffers(1, &mCanvasVertexBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mCanvasVertexBufferId, sizeof(Vertex2D) * MaxCanvasVertexCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT));

    YAWN_GL_CHECK(glCreateBuffers(1, &mCanvasIndexBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mCanvasIndexBufferId, sizeof(unsigned short) * MaxCanvasIndexCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT));

    YAWN_GL_CHECK(glCreateVertexArrays(1, &mCanvasVertexArrayObjectId));

    YAWN_GL_CHECK(glVertexArrayVertexBuffer(mCanvasVertexArrayObjectId, 0, mCanvasVertexBufferId, 0, sizeof(Vertex2D)));
    YAWN_GL_CHECK(glVertexArrayElementBuffer(mCanvasVertexArrayObjectId, mCanvasIndexBufferId));

    YAWN_GL_CHECK(glEnableVertexArrayAttrib(mCanvasVertexArrayObjectId, 0));
    YAWN_GL_CHECK(glEnableVertexArrayAttrib(mCanvasVertexArrayObjectId, 1));
    YAWN_GL_CHECK(glEnableVertexArrayAttrib(mCanvasVertexArrayObjectId, 2));

    YAWN_GL_CHECK(glVertexArrayAttribFormat(mCanvasVertexArrayObjectId, 0, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex2D, Position)));
    YAWN_GL_CHECK(glVertexArrayAttribFormat(mCanvasVertexArrayObjectId, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex2D, UV)));
    YAWN_GL_CHECK(glVertexArrayAttribFormat(mCanvasVertexArrayObjectId, 2, 4, GL_UNSIGNED_BYTE, GL_TRUE, offsetof(Vertex2D, Color)));

    YAWN_GL_CHECK(glVertexArrayAttribBinding(mCanvasVertexArrayObjectId, 0, 0));
    YAWN_GL_CHECK(glVertexArrayAttribBinding(mCanvasVertexArrayObjectId, 1, 0));
    YAWN_GL_CHECK(glVertexArrayAttribBinding(mCanvasVertexArrayObjectId, 2, 0));

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, mGlobalBufferId);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, mInstanceBufferId);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, mMeshBufferId);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, mSamplerBufferId);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, mDrawBufferId);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, mMaterialBufferId);

    mCullingProgramId = CompileShader(Culling_comp);
    mForwardProgramId = CompileShader(Forward_vert, Forward_frag);
    mCanvasProgramId = CompileShader(Canvas_vert, Canvas_frag);

    YAWN_GL_CHECK(glPixelStorei(GL_PACK_ALIGNMENT, 1));
    YAWN_GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

    //mInstances = (GPUInstanceData*)glMapNamedBuffer(mInstanceBufferId, GL_READ_WRITE);
    //mMeshes = (GPUMeshData*)glMapNamedBuffer(mMeshBufferId, GL_READ_WRITE);

    mGlobalData.FramebufferSize = Window::GetSize();
}

RendererDriverOpenGL::~RendererDriverOpenGL() {
    //YAWN_GL_CHECK(glUnmapNamedBuffer(mMeshBufferId));
    //YAWN_GL_CHECK(glUnmapNamedBuffer(mInstanceBufferId));

    YAWN_GL_CHECK(glDeleteProgramPipelines(1, &mCanvasProgramId));
    YAWN_GL_CHECK(glDeleteProgramPipelines(1, &mForwardProgramId));
    YAWN_GL_CHECK(glDeleteProgramPipelines(1, &mCullingProgramId));

    YAWN_GL_CHECK(glDeleteVertexArrays(1, &mCanvasVertexArrayObjectId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mCanvasIndexBufferId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mCanvasVertexBufferId));
    YAWN_GL_CHECK(glDeleteVertexArrays(1, &mVertexArrayObjectId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mIndexBufferId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mVertexBufferId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mDrawBufferId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mSamplerBufferId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mMeshBufferId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mMaterialBufferId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mInstanceBufferId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mGlobalBufferId));
}

void RendererDriverOpenGL::SetFramebufferSize(const Vector2& size) {
    glViewport(0, 0, Math::FastFloatToInt(size.X), Math::FastFloatToInt(size.Y));

    mGlobalData.FramebufferSize = size;
}

void RendererDriverOpenGL::SetCameraProjection(const Matrix4& projection) {
    mGlobalData.Projection = projection;
}

void RendererDriverOpenGL::SetCameraTransform(const Matrix4& transform) {
    mGlobalData.View = Matrix4::Invert(transform);
    mGlobalData.CameraPosition = Vector4(Matrix4::ExtractPosition(transform), 1.0f);
}

int RendererDriverOpenGL::CreateViewport(int width, int height, bool directToScreen) {
    int id = Base::CreateViewport(width, height, directToScreen);

    mViewports.Expand(id + 1);

    mViewports[id] = GPUViewportData();

    mViewports[id].Width = width;
    mViewports[id].Height = height;

    if (directToScreen) {
        mViewports[id].FramebufferId = 0;
    } else {
        mViewports[id].ColorTextureId = CreateTexture(width, height, TextureFormat::RGBA8, TextureFilter::Linear, TextureWrapping::ClampToEdge, 1);
        mViewports[id].DepthTextureId = CreateTexture(width, height, TextureFormat::D24, TextureFilter::Linear, TextureWrapping::ClampToEdge, 1);

        YAWN_GL_CHECK(glCreateFramebuffers(1, &mViewports[id].FramebufferId));
        YAWN_GL_CHECK(glNamedFramebufferTexture(mViewports[id].FramebufferId, GL_COLOR_ATTACHMENT0, mTextureIds[mViewports[id].ColorTextureId], 0));
        YAWN_GL_CHECK(glNamedFramebufferTexture(mViewports[id].FramebufferId, GL_DEPTH_ATTACHMENT, mTextureIds[mViewports[id].DepthTextureId], 0));

        YAWN_ASSERT(glCheckNamedFramebufferStatus(mViewports[id].FramebufferId, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    }

    return id;
}

void RendererDriverOpenGL::DestroyViewport(int id) {
    if (mViewports[id].FramebufferId) {
        glDeleteFramebuffers(1, &mViewports[id].FramebufferId);

        DestroyTexture(mViewports[id].DepthTextureId);
        DestroyTexture(mViewports[id].ColorTextureId);
    }

    Base::DestroyViewport(id);
}

void RendererDriverOpenGL::SetViewportSize(int id, int width, int height) {
    if (mViewports[id].FramebufferId && (mViewports[id].Width != width || mViewports[id].Height != height)) {
        DestroyTexture(mViewports[id].DepthTextureId);
        DestroyTexture(mViewports[id].ColorTextureId);

        mViewports[id].Width = width;
        mViewports[id].Height = height;

        mViewports[id].ColorTextureId = CreateTexture(width, height, TextureFormat::RGBA8, TextureFilter::Linear, TextureWrapping::ClampToEdge, 1);
        mViewports[id].DepthTextureId = CreateTexture(width, height, TextureFormat::D24, TextureFilter::Linear, TextureWrapping::ClampToEdge, 1);

        YAWN_GL_CHECK(glNamedFramebufferTexture(mViewports[id].FramebufferId, GL_COLOR_ATTACHMENT0, mTextureIds[mViewports[id].ColorTextureId], 0));
        YAWN_GL_CHECK(glNamedFramebufferTexture(mViewports[id].FramebufferId, GL_DEPTH_ATTACHMENT, mTextureIds[mViewports[id].DepthTextureId], 0));

        YAWN_ASSERT(glCheckNamedFramebufferStatus(mViewports[id].FramebufferId, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    }
}

int RendererDriverOpenGL::GetViewportColorTexture(int id) const {
    return mViewports[id].ColorTextureId;
}

int RendererDriverOpenGL::CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount) {
    int id = Base::CreateTexture(width, height, format, filter, wrapping, mipmapCount);

    mTextureIds.Expand(id + 1, 0);

    YAWN_GL_CHECK(glCreateTextures(GL_TEXTURE_2D, 1, &mTextureIds[id]));

    YAWN_GL_CHECK(glTextureParameteri(mTextureIds[id], GL_TEXTURE_WRAP_S, GL_REPEAT));
    YAWN_GL_CHECK(glTextureParameteri(mTextureIds[id], GL_TEXTURE_WRAP_T, GL_REPEAT));

    switch (filter) {
    case TextureFilter::Nearest:
        YAWN_GL_CHECK(glTextureParameteri(mTextureIds[id], GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
        YAWN_GL_CHECK(glTextureParameteri(mTextureIds[id], GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        break;
    case TextureFilter::Linear:
        YAWN_GL_CHECK(glTextureParameteri(mTextureIds[id], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
        YAWN_GL_CHECK(glTextureParameteri(mTextureIds[id], GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        break;
    case TextureFilter::Anisotropic:
        YAWN_GL_CHECK(glTextureParameteri(mTextureIds[id], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
        YAWN_GL_CHECK(glTextureParameteri(mTextureIds[id], GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        // YAWN_GL_CHECK(glTextureParameterf(mTextureIds[id], GL_TEXTURE_MAX_ANISOTROPY_EXT, mMaxAnisotropy));
        break;
    }

    switch (format) {
    case TextureFormat::D24:
        YAWN_GL_CHECK(glTextureStorage2D(mTextureIds[id], mipmapCount, GL_DEPTH_COMPONENT24, width, height));
        break;
    case TextureFormat::R8:
        YAWN_GL_CHECK(glTextureStorage2D(mTextureIds[id], mipmapCount, GL_R8, width, height));
        break;
    case TextureFormat::RG8:
        YAWN_GL_CHECK(glTextureStorage2D(mTextureIds[id], mipmapCount, GL_RG8, width, height));
        break;
    case TextureFormat::RGBA8:
        YAWN_GL_CHECK(glTextureStorage2D(mTextureIds[id], mipmapCount, GL_RGBA8, width, height));
        break;
    case TextureFormat::BC1:
        YAWN_GL_CHECK(glTextureStorage2D(mTextureIds[id], mipmapCount, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, width, height));
        break;
    case TextureFormat::BC3:
        YAWN_GL_CHECK(glTextureStorage2D(mTextureIds[id], mipmapCount, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, width, height));
        break;
    }

    GLuint64 handle;
    YAWN_GL_CHECK(handle = glGetTextureHandleARB(mTextureIds[id]));
    YAWN_GL_CHECK(glMakeTextureHandleResidentARB(handle));

    YAWN_GL_CHECK(glNamedBufferSubData(mSamplerBufferId, sizeof(GLuint64) * id, sizeof(GLuint64), &handle));
    return id;
}

void RendererDriverOpenGL::DestroyTexture(int id) {
    YAWN_GL_CHECK(glDeleteTextures(1, &mTextureIds[id]));

    Base::DestroyTexture(id);
}

void RendererDriverOpenGL::SetTextureData(int id, int mipmap, const void* data) {
    int width, height, format;
    YAWN_GL_CHECK(glGetTextureLevelParameteriv(mTextureIds[id], mipmap, GL_TEXTURE_WIDTH, &width));
    YAWN_GL_CHECK(glGetTextureLevelParameteriv(mTextureIds[id], mipmap, GL_TEXTURE_HEIGHT, &height));
    YAWN_GL_CHECK(glGetTextureLevelParameteriv(mTextureIds[id], mipmap, GL_TEXTURE_INTERNAL_FORMAT, &format));

    switch (format) {
    case GL_R8:
        YAWN_GL_CHECK(glTextureSubImage2D(mTextureIds[id], mipmap, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE, data));
        break;
    case GL_RG8:
        YAWN_GL_CHECK(glTextureSubImage2D(mTextureIds[id], mipmap, 0, 0, width, height, GL_RG, GL_UNSIGNED_BYTE, data));
        break;
    case GL_RGBA8:
        YAWN_GL_CHECK(glTextureSubImage2D(mTextureIds[id], mipmap, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data));
        break;
    case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
        YAWN_GL_CHECK(glCompressedTextureSubImage2D(mTextureIds[id], mipmap, 0, 0, width, height, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, width * height / 2, data));
        break;
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
        YAWN_GL_CHECK(glCompressedTextureSubImage2D(mTextureIds[id], mipmap, 0, 0, width, height, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, width * height, data));
        break;
    }
}

Vector2 RendererDriverOpenGL::GetTextureSize(int id) const {
    float width, height;
    YAWN_GL_CHECK(glGetTextureLevelParameterfv(mTextureIds[id], 0, GL_TEXTURE_WIDTH, &width));
    YAWN_GL_CHECK(glGetTextureLevelParameterfv(mTextureIds[id], 0, GL_TEXTURE_HEIGHT, &height));
    return Vector2(width, height);
}

int RendererDriverOpenGL::GetWhiteTexture() {
    if (mWhiteTextureId == Pool::None) {
        mWhiteTextureId = CreateTexture(4, 4, TextureFormat::RGBA8, TextureFilter::Anisotropic, TextureWrapping::Repeat, 1);

        Color4 pixels[16] = {
            Color::White, Color::White, Color::White, Color::White,
            Color::White, Color::White, Color::White, Color::White,
            Color::White, Color::White, Color::White, Color::White,
            Color::White, Color::White, Color::White, Color::White,
        };

        SetTextureData(mWhiteTextureId, 0, pixels);
    }

    return mWhiteTextureId;
}

int RendererDriverOpenGL::CreateMaterial() {
    int id = Base::CreateMaterial();

    mMaterials.Expand(id + 1);
    mMaterials[id] = GPUMaterialData();

    YAWN_GL_CHECK(glNamedBufferSubData(mMaterialBufferId, id * sizeof(GPUMaterialData), sizeof(GPUMaterialData), &mMaterials[id]));

    return id;
}

void RendererDriverOpenGL::DestroyMaterial(int id) {
    mMaterials[id] = GPUMaterialData();

    YAWN_GL_CHECK(glNamedBufferSubData(mMaterialBufferId, id * sizeof(GPUMaterialData), sizeof(GPUMaterialData), &mMaterials[id]));

    Base::DestroyMaterial(id);
}

void RendererDriverOpenGL::SetMaterialBaseColor(int id, const Color4& color) {
    mMaterials[id].BaseColor = color;

    YAWN_GL_CHECK(glNamedBufferSubData(mMaterialBufferId, id * sizeof(GPUMaterialData), sizeof(GPUMaterialData), &mMaterials[id]));
}

void RendererDriverOpenGL::SetMaterialRoughness(int id, float roughness) {
    mMaterials[id].Roughness = roughness;

    YAWN_GL_CHECK(glNamedBufferSubData(mMaterialBufferId, id * sizeof(GPUMaterialData), sizeof(GPUMaterialData), &mMaterials[id]));
}

void RendererDriverOpenGL::SetMaterialMetallic(int id, float metallic) {
    mMaterials[id].Metallic = metallic;

    YAWN_GL_CHECK(glNamedBufferSubData(mMaterialBufferId, id * sizeof(GPUMaterialData), sizeof(GPUMaterialData), &mMaterials[id]));
}

void RendererDriverOpenGL::SetMaterialOcclusionStrength(int id, float strength) {
    mMaterials[id].OcclusionStrength = strength;

    YAWN_GL_CHECK(glNamedBufferSubData(mMaterialBufferId, id * sizeof(GPUMaterialData), sizeof(GPUMaterialData), &mMaterials[id]));
}

void RendererDriverOpenGL::SetMaterialAlbedoTexture(int id, int textureId) {
    mMaterials[id].AlbedoTextureId = IsTextureValid(textureId) ? textureId : Pool::None;

    YAWN_GL_CHECK(glNamedBufferSubData(mMaterialBufferId, id * sizeof(GPUMaterialData), sizeof(GPUMaterialData), &mMaterials[id]));
}

void RendererDriverOpenGL::SetMaterialNormalTexture(int id, int textureId) {
    mMaterials[id].NormalTextureId = IsTextureValid(textureId) ? textureId : Pool::None;

    YAWN_GL_CHECK(glNamedBufferSubData(mMaterialBufferId, id * sizeof(GPUMaterialData), sizeof(GPUMaterialData), &mMaterials[id]));
}

void RendererDriverOpenGL::SetMaterialMetallicRoughnessTexture(int id, int textureId) {
    mMaterials[id].MetallicRoughnessTextureId = IsTextureValid(textureId) ? textureId : Pool::None;

    YAWN_GL_CHECK(glNamedBufferSubData(mMaterialBufferId, id * sizeof(GPUMaterialData), sizeof(GPUMaterialData), &mMaterials[id]));
}

void RendererDriverOpenGL::SetMaterialEmissiveTexture(int id, int textureId) {
    mMaterials[id].EmissiveTextureId = IsTextureValid(textureId) ? textureId : Pool::None;

    YAWN_GL_CHECK(glNamedBufferSubData(mMaterialBufferId, id * sizeof(GPUMaterialData), sizeof(GPUMaterialData), &mMaterials[id]));
}

void RendererDriverOpenGL::SetMaterialOcclusionTexture(int id, int textureId) {
    mMaterials[id].OcclusionTextureId = IsTextureValid(textureId) ? textureId : Pool::None;

    YAWN_GL_CHECK(glNamedBufferSubData(mMaterialBufferId, id * sizeof(GPUMaterialData), sizeof(GPUMaterialData), &mMaterials[id]));
}

int RendererDriverOpenGL::CreateMesh(int vertexCount, int indexCount) {
    int id = Base::CreateMesh(vertexCount, indexCount);

    mMeshes.Expand(id + 1);

    mMeshes[id].VertexOffset = mGlobalVertexOffset;
    mMeshes[id].VertexCount = vertexCount;
    mMeshes[id].IndexOffset = mGlobalIndexOffset;
    mMeshes[id].IndexCount = indexCount;

    YAWN_GL_CHECK(glNamedBufferSubData(mMeshBufferId, id * sizeof(GPUMeshData), sizeof(GPUMeshData), &mMeshes[id]));

    mGlobalVertexOffset += vertexCount;
    mGlobalIndexOffset += indexCount;

    return id;
}

void RendererDriverOpenGL::DestroyMesh(int id) {
    mMeshes[id].VertexOffset = 0;
    mMeshes[id].IndexOffset = 0;
    mMeshes[id].IndexCount = 0;

    Base::DestroyMesh(id);
}

void RendererDriverOpenGL::SetMeshData(int id, const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices) {
    YAWN_ASSERT(mMeshes[id].VertexCount == vertices.GetSize());
    YAWN_ASSERT(mMeshes[id].IndexCount == indices.GetSize());

    YAWN_GL_CHECK(glNamedBufferSubData(mVertexBufferId, mMeshes[id].VertexOffset * sizeof(Vertex3D), mMeshes[id].VertexCount * sizeof(Vertex3D), vertices.GetData()));
    YAWN_GL_CHECK(glNamedBufferSubData(mIndexBufferId, mMeshes[id].IndexOffset * sizeof(int), mMeshes[id].IndexCount * sizeof(int), indices.GetData()));
}

int RendererDriverOpenGL::CreateInstance() {
    int id = Base::CreateInstance();

    mInstances.Expand(id + 1);

    mInstances[id] = GPUInstanceData();

    YAWN_GL_CHECK(glNamedBufferSubData(mInstanceBufferId, id * sizeof(GPUInstanceData), sizeof(GPUInstanceData), &mInstances[id]));

    return id;
}

void RendererDriverOpenGL::DestroyInstance(int id) {
    mInstances[id] = GPUInstanceData();

    YAWN_GL_CHECK(glNamedBufferSubData(mInstanceBufferId, id * sizeof(GPUInstanceData), sizeof(GPUInstanceData), &mInstances[id]));

    RendererDriver::DestroyInstance(id);
}

void RendererDriverOpenGL::SetInstanceTransform(int id, const Matrix4& transform) {
    mInstances[id].Transform = transform;

    YAWN_GL_CHECK(glNamedBufferSubData(mInstanceBufferId, id * sizeof(GPUInstanceData), sizeof(GPUInstanceData), &mInstances[id]));
}

void RendererDriverOpenGL::SetInstanceMaterial(int id, int materialId) {
    mInstances[id].MaterialId = IsMaterialValid(materialId) ? materialId : Pool::None;

    YAWN_GL_CHECK(glNamedBufferSubData(mInstanceBufferId, id * sizeof(GPUInstanceData), sizeof(GPUInstanceData), &mInstances[id]));
}

void RendererDriverOpenGL::SetInstanceMesh(int id, int meshId) {
    mInstances[id].MeshId = IsMeshValid(meshId) ? meshId : Pool::None;

    YAWN_GL_CHECK(glNamedBufferSubData(mInstanceBufferId, id * sizeof(GPUInstanceData), sizeof(GPUInstanceData), &mInstances[id]));
}

void RendererDriverOpenGL::SetInstanceViewport(int id, int viewportId) {
    mInstances[id].ViewportId = IsViewportValid(viewportId) ? viewportId : Pool::None;

    YAWN_GL_CHECK(glNamedBufferSubData(mInstanceBufferId, id * sizeof(GPUInstanceData), sizeof(GPUInstanceData), &mInstances[id]));
}

int RendererDriverOpenGL::CreateCanvasItem() {
    int id = Base::CreateCanvasItem();

    mCanvasItems.Expand(id + 1);
    mCanvasVertexBuffers.Expand(id + 1);
    mCanvasIndexBuffers.Expand(id + 1);

    mCanvasItems[id] = GPUCanvasItemData();
    mCanvasVertexBuffers[id] = 0;
    mCanvasIndexBuffers[id] = 0;

    return id;
}

void RendererDriverOpenGL::DestroyCanvasItem(int id) {
    YAWN_GL_CHECK(glDeleteBuffers(1, &mCanvasIndexBuffers[id]));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mCanvasVertexBuffers[id]));

    mCanvasItems[id] = GPUCanvasItemData();

    Base::DestroyCanvasItem(id);
}

void RendererDriverOpenGL::SetCanvasItemData(int id, const ArrayView<const Vertex2D>& vertices, const ArrayView<const int>& indices) {
    GPUCanvasItemData& canvasItem = mCanvasItems[id];

    canvasItem.VertexOffset = 0;
    canvasItem.IndexOffset = 0;
    canvasItem.VertexCount = vertices.GetSize();
    canvasItem.IndexCount = indices.GetSize();

    if (!mCanvasVertexBuffers[id] || vertices.GetSize() > canvasItem.VertexCapacity) {
        YAWN_GL_CHECK(glDeleteBuffers(1, &mCanvasVertexBuffers[id]));
        YAWN_GL_CHECK(glCreateBuffers(1, &mCanvasVertexBuffers[id]));

        YAWN_GL_CHECK(glNamedBufferStorage(mCanvasVertexBuffers[id], vertices.GetSizeInBytes(), vertices.GetData(), GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT));
        
        canvasItem.VertexCapacity = canvasItem.VertexCount;
    } else {
        YAWN_GL_CHECK(glNamedBufferSubData(mCanvasVertexBuffers[id], 0, vertices.GetSizeInBytes(), vertices.GetData()));
    }

    if (!mCanvasIndexBuffers[id] || vertices.GetSize() > canvasItem.IndexCapacity) {
        YAWN_GL_CHECK(glDeleteBuffers(1, &mCanvasIndexBuffers[id]));
        YAWN_GL_CHECK(glCreateBuffers(1, &mCanvasIndexBuffers[id]));

        YAWN_GL_CHECK(glNamedBufferStorage(mCanvasIndexBuffers[id], indices.GetSizeInBytes(), indices.GetData(), GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT));
        
        canvasItem.IndexCapacity = canvasItem.IndexCount;
    } else {
        YAWN_GL_CHECK(glNamedBufferSubData(mCanvasIndexBuffers[id], 0, indices.GetSizeInBytes(), indices.GetData()));
    }
}

void RendererDriverOpenGL::SetCanvasItemTexture(int id, int textureId) {
}

void RendererDriverOpenGL::DrawCanvasItem(int id, int vertexOffset, int indexOffset, int indexCount) {
    CanvasDrawCommand command;
    command.CanvasItemId = id;
    command.VertexOffset = vertexOffset;
    command.IndexOffset = indexOffset;
    command.IndexCount = indexCount;
    mCanvasDrawCommands.Add(command);
}

void RendererDriverOpenGL::Render() {
    mGlobalData.ProjectionView = mGlobalData.Projection * mGlobalData.View;
    mGlobalData.InvertedProjectionView = Matrix4::Invert(mGlobalData.ProjectionView);
    mGlobalData.InstanceCount = mInstancePool.GetSize();

    YAWN_GL_CHECK(glNamedBufferSubData(mGlobalBufferId, 0, sizeof(GPUGlobalData), &mGlobalData));

    YAWN_GL_CHECK(glDisable(GL_SCISSOR_TEST));

    YAWN_GL_CHECK(glEnable(GL_DEPTH_TEST));
    YAWN_GL_CHECK(glDisable(GL_CULL_FACE));
    YAWN_GL_CHECK(glDisable(GL_BLEND));

    for (int viewportId = 0; viewportId < mViewportPool.GetSize(); ++viewportId) {
        if (mViewportPool.IsValid(viewportId)) {
            mGlobalData.CurrentViewportId = viewportId;

            YAWN_GL_CHECK(glNamedBufferSubData(mGlobalBufferId, offsetof(GPUGlobalData, CurrentViewportId), sizeof(int), &mGlobalData.CurrentViewportId));

            YAWN_GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, mViewports[viewportId].FramebufferId));

            YAWN_GL_CHECK(glViewport(0, 0, mViewports[viewportId].Width, mViewports[viewportId].Height));

            YAWN_GL_CHECK(glClearColor(mClearColor.R, mClearColor.G, mClearColor.B, mClearColor.A));
            YAWN_GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

            YAWN_GL_CHECK(glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT));

            YAWN_GL_CHECK(glBindProgramPipeline(mCullingProgramId));

            YAWN_GL_CHECK(glDispatchCompute(Math::Align(mGlobalData.InstanceCount, 64) / 64, 1, 1));

            YAWN_GL_CHECK(glBindProgramPipeline(mForwardProgramId));

            YAWN_GL_CHECK(glBindVertexArray(mVertexArrayObjectId));

            YAWN_GL_CHECK(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, mDrawBufferId));

            YAWN_GL_CHECK(glMemoryBarrier(GL_COMMAND_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT));

            YAWN_GL_CHECK(glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, mGlobalData.InstanceCount, sizeof(GPUDrawElementsIndirectCommand)));
        }
    }

    YAWN_GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

    YAWN_GL_CHECK(glViewport(0, 0, Math::FastFloatToInt(mGlobalData.FramebufferSize.X), Math::FastFloatToInt(mGlobalData.FramebufferSize.Y)));

    YAWN_GL_CHECK(glBindProgramPipeline(mCanvasProgramId));

    YAWN_GL_CHECK(glBindVertexArray(mCanvasVertexArrayObjectId));

    YAWN_GL_CHECK(glDisable(GL_DEPTH_TEST));
    YAWN_GL_CHECK(glDisable(GL_CULL_FACE));
    YAWN_GL_CHECK(glEnable(GL_BLEND));
    YAWN_GL_CHECK(glBlendEquation(GL_FUNC_ADD));
    YAWN_GL_CHECK(glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA));

    YAWN_GL_CHECK(glEnable(GL_SCISSOR_TEST));

    LLSetClipRect(Rectangle(Vector2::Zero, mGlobalData.FramebufferSize));
}

void RendererDriverOpenGL::LLSetVertexBufferData2D(const ArrayView<const Vertex2D>& vertices) {
    if (vertices.GetSize() > 0) {
        Vertex2D* canvasVertices = (Vertex2D*)glMapNamedBuffer(mCanvasVertexBufferId, GL_WRITE_ONLY);

        Memory::Copy(canvasVertices, vertices.GetData(), vertices.GetSizeInBytes());

        YAWN_GL_CHECK(glUnmapNamedBuffer(mCanvasVertexBufferId));
    }
}

void RendererDriverOpenGL::LLSetIndexBufferData2D(const ArrayView<const unsigned short>& indices) {
    if (indices.GetSize() > 0) {
        unsigned short* canvasIndices = (GLushort*)glMapNamedBuffer(mCanvasIndexBufferId, GL_WRITE_ONLY);

        Memory::Copy(canvasIndices, indices.GetData(), indices.GetSizeInBytes());

        YAWN_GL_CHECK(glUnmapNamedBuffer(mCanvasIndexBufferId));
    }
}

void RendererDriverOpenGL::LLSetTexture2D(int textureId) {
    int newTextureId = IsTextureValid(textureId) ? textureId : GetWhiteTexture();

    if (mGlobalData.TextureId != newTextureId) {
        mGlobalData.TextureId = newTextureId;

        YAWN_GL_CHECK(glNamedBufferSubData(mGlobalBufferId, offsetof(GPUGlobalData, TextureId), sizeof(mGlobalData.TextureId), &mGlobalData.TextureId));
    }
}

void RendererDriverOpenGL::LLSetClipRect(const Rectangle& clipRect) {
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    YAWN_GL_CHECK(glScissor(
        Math::FastFloatToInt(clipRect.Position.X),
        Math::FastFloatToInt(viewport[3] - clipRect.GetEnd().Y), 
        Math::FastFloatToInt(clipRect.Size.X),
        Math::FastFloatToInt(clipRect.Size.Y)
    ));
}

void RendererDriverOpenGL::LLDraw2D(Topology topology, int vertexOffset, int indexOffset, int indexCount) {
    if (indexCount > 0) {
        GLenum type = GL_NONE;
        switch (topology) {
        case Topology::Points: type = GL_POINTS; break;
        case Topology::Lines: type = GL_LINES; break;
        case Topology::Triangles: type = GL_TRIANGLES; break;
        }

        if (type != GL_NONE) {
            YAWN_GL_CHECK(glDrawElementsBaseVertex(type, indexCount, GL_UNSIGNED_SHORT, (void*)(intptr_t)(indexOffset * sizeof(unsigned short)), vertexOffset));
        }
    }
}

GLuint RendererDriverOpenGL::CompileShader(ArrayView<const char> vertexCode, ArrayView<const char> fragmentCode) {
    const char* vertexShaderCode = vertexCode.GetData();
    const char* fragmentShaderCode = fragmentCode.GetData();

    GLuint vertexShader;
    YAWN_GL_CHECK(vertexShader = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vertexShaderCode));

    GLuint fragmentShader;
    YAWN_GL_CHECK(fragmentShader = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fragmentShaderCode));

    TestShader(vertexShader);
    TestShader(fragmentShader);

    GLuint programPipeline = 0;
    YAWN_GL_CHECK(glCreateProgramPipelines(1, &programPipeline));
    YAWN_GL_CHECK(glUseProgramStages(programPipeline, GL_VERTEX_SHADER_BIT, vertexShader));
    YAWN_GL_CHECK(glUseProgramStages(programPipeline, GL_FRAGMENT_SHADER_BIT, fragmentShader));

    return programPipeline;
}

GLuint RendererDriverOpenGL::CompileShader(ArrayView<const char> computeCode) {
    const char* computeShaderCode = computeCode.GetData();

    GLuint computeShader;
    YAWN_GL_CHECK(computeShader = glCreateShaderProgramv(GL_COMPUTE_SHADER, 1, &computeShaderCode));

    TestShader(computeShader);

    GLuint programPipeline = 0;
    YAWN_GL_CHECK(glCreateProgramPipelines(1, &programPipeline));
    YAWN_GL_CHECK(glUseProgramStages(programPipeline, GL_COMPUTE_SHADER_BIT, computeShader));

    return programPipeline;
}

void RendererDriverOpenGL::TestShader(GLuint shaderProgram) {
    GLint result, infoLength;
    YAWN_GL_CHECK(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result));
    YAWN_GL_CHECK(glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLength));
    if (!result && infoLength > 0) {
        Array<char> message(infoLength + 1);
        YAWN_GL_CHECK(glGetProgramInfoLog(shaderProgram, infoLength, nullptr, &message[0]));

        Console::WriteLine(String::FromUTF8(message.GetData()));
    }
}

void RendererDriverOpenGL::CheckError(const wchar_t* path, int line, const wchar_t* expression) const {
    GLenum errorCode = glGetError();

    if (errorCode != GL_NO_ERROR) {
        const wchar_t* filename = path;

        for (const wchar_t* p = filename; *p; ++p) {
            if (*p == L'/' || *p == L'\\') {
                filename = p + 1;
            }
        }

        const wchar_t* error = L"Unknown error";
        const wchar_t* description = L"No description";

        switch (errorCode) {
            case GL_INVALID_ENUM: {
                error = L"GL_INVALID_ENUM";
                description = L"An unacceptable value has been specified for an enumerated argument.";
                break;
            }

            case GL_INVALID_VALUE: {
                error = L"GL_INVALID_VALUE";
                description = L"A numeric argument is out of range.";
                break;
            }

            case GL_INVALID_OPERATION: {
                error = L"GL_INVALID_OPERATION";
                description = L"The specified operation is not allowed in the current state.";
                break;
            }

            case GL_STACK_OVERFLOW: {
                error = L"GL_STACK_OVERFLOW";
                description = L"This command would cause a stack overflow.";
                break;
            }

            case GL_STACK_UNDERFLOW: {
                error = L"GL_STACK_UNDERFLOW";
                description = L"This command would cause a stack underflow.";
                break;
            }

            case GL_OUT_OF_MEMORY: {
                error = L"GL_OUT_OF_MEMORY";
                description = L"There is not enough memory left to execute the command.";
                break;
            }

            case GL_INVALID_FRAMEBUFFER_OPERATION: {
                error = L"GL_INVALID_FRAMEBUFFER_OPERATION";
                description = L"The object bound to FRAMEBUFFER_BINDING is not \"framebuffer complete\".";
                break;
            }
        }

        Console::Write(L"An internal OpenGL call failed in %s:%d.\n  Expression:\n    %s\n  Description:\n    %s\n    %s\n\n",
            filename, line, expression, error, description);
    }
}

void RendererDriverOpenGL::DefragmentateCanvasItemData() {
}
