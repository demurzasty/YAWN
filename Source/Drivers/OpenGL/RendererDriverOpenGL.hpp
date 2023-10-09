#pragma once 

#include <YAWN/Graphics/RendererDriver.hpp>

#include <GL/glew.h>

#ifdef _DEBUG
#define YAWN_GL_CHECK(expr)                                          \
    do {                                                             \
        (expr);                                                      \
        CheckError(YAWN_WIDE(__FILE__), __LINE__, YAWN_WIDE(#expr)); \
    } while (false)
#else
#define YAWN_GL_CHECK(expr) (expr)
#endif

namespace YAWN {
    class RendererDriverOpenGL : public RendererDriver {
        YAWN_OBJECT(RendererDriverOpenGL, RendererDriver);

    public:
        RendererDriverOpenGL();

        ~RendererDriverOpenGL() override;

        void SetFramebufferSize(const Vector2& size) override;

        void SetCameraProjection(const Matrix4& projection) override;

        void SetCameraTransform(const Matrix4& transform) override;

        OID CreateViewport(int width, int height, bool directToScreen) override;

        void DestroyViewport(OID id) override;

        void SetViewportSize(OID id, int width, int height) override;

        OID GetViewportColorTexture(OID id) const override;

        OID CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount) override;

        void DestroyTexture(OID id) override;

        void SetTextureData(OID id, int mipmap, const void* data) override;

        Vector2 GetTextureSize(OID id) const override;

        OID GetWhiteTexture() override;

        OID CreateMaterial() override;

        void DestroyMaterial(OID id) override;

        void SetMaterialBaseColor(OID id, const Color4& color) override;

        void SetMaterialRoughness(OID id, float roughness) override;

        void SetMaterialMetallic(OID id, float metallic) override;

        void SetMaterialOcclusionStrength(OID id, float strength) override;

        void SetMaterialAlbedoTexture(OID id, OID textureId) override;

        void SetMaterialNormalTexture(OID id, OID textureId) override;

        void SetMaterialMetallicRoughnessTexture(OID id, OID textureId) override;

        void SetMaterialEmissiveTexture(OID id, OID textureId) override;

        void SetMaterialOcclusionTexture(OID id, OID textureId) override;

        OID CreateMesh(int vertexCount, int indexCount) override;

        void DestroyMesh(OID id) override;

        void SetMeshData(OID id, const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices) override;

        OID CreateInstance() override;

        void DestroyInstance(OID id) override;

        void SetInstanceTransform(OID id, const Matrix4& transform) override;

        void SetInstanceMaterial(OID id, OID materialId) override;

        void SetInstanceMesh(OID id, OID meshId) override;

        void SetInstanceViewport(OID id, OID viewportId) override;

        OID CreateCanvasItem() override;

        void DestroyCanvasItem(OID id) override;

        void SetCanvasItemData(OID id, const ArrayView<const Vertex2D>& vertices, const ArrayView<const int>& indices) override;

        void SetCanvasItemTexture(OID id, OID textureId) override;

        void DrawCanvasItem(OID id, int vertexOffset, int indexOffset, int indexCount) override;

        void Render() override;

    public:
        void LLSetVertexBufferData2D(const ArrayView<const Vertex2D>& vertices) override;

        void LLSetIndexBufferData2D(const ArrayView<const unsigned short>& indices) override;

        void LLSetTexture2D(OID textureId) override;

        void LLSetClipRect(const Rectangle& clipRect) override;

        void LLDraw2D(Topology topology, int vertexOffset, int indexOffset, int indexCount) override;

    private:
        GLuint CompileShader(ArrayView<const char> vertexCode, ArrayView<const char> fragmentCode);

        GLuint CompileShader(ArrayView<const char> computeCode);

        void TestShader(GLuint shaderProgram);

        void CheckError(const wchar_t* path, int line, const wchar_t* expression) const;

        void DefragmentateCanvasItemData();

    private:
        struct GPUDrawElementsIndirectCommand {
            int IndexCount = 0;
            int InstanceCount = 0;
            int IndexOffset = 0;
            int VertexOffset = 0;
            int FirstInstance = 0;
        };

        struct GPUViewportData {
            GLuint FramebufferId = 0;
            OID ColorTextureId;
            OID DepthTextureId;
            int Width = 0;
            int Height = 0;
        };

        struct CanvasDrawCommand {
            int CanvasItemId;
            int VertexOffset;
            int IndexOffset;
            int IndexCount;
        };

        GLuint mGlobalBufferId = 0;
        GLuint mInstanceBufferId = 0;
        GLuint mMaterialBufferId = 0;
        GLuint mMeshBufferId = 0;
        GLuint mSamplerBufferId = 0;
        GLuint mDrawBufferId = 0;
        GLuint mVertexBufferId = 0;
        GLuint mIndexBufferId = 0;
        GLuint mVertexArrayObjectId = 0;

        GLuint mCanvasVertexBufferId = 0;
        GLuint mCanvasIndexBufferId = 0;
        GLuint mCanvasVertexArrayObjectId = 0;

        GLuint mCullingProgramId = 0;
        GLuint mForwardProgramId = 0;
        GLuint mCanvasProgramId = 0;

        GPUGlobalData mGlobalData;
        Array<GPUInstanceData> mInstances;
        Array<GPUMeshData> mMeshes;
        Array<GPUMaterialData> mMaterials;

        int mGlobalVertexOffset = 0;
        int mGlobalIndexOffset = 0;
        int mGlobalCanvasVertexOffset = 0;
        int mGlobalCanvasIndexOffset = 0;

        Array<GLuint> mTextureIds;

        Array<GPUCanvasItemData> mCanvasItems;
        Array<GLuint> mCanvasVertexBuffers;
        Array<GLuint> mCanvasIndexBuffers;

        Array<GPUViewportData> mViewports;

        Array<CanvasDrawCommand> mCanvasDrawCommands;

        OID mWhiteTextureId = Pool::None;
    };
}
