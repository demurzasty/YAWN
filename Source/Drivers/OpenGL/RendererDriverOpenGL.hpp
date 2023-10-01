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

        int CreateViewport(int width, int height, bool directToScreen) override;

        void DestroyViewport(int id) override;

        void SetViewportSize(int id, int width, int height) override;

        int GetViewportColorTexture(int id) const override;

        int CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount) override;

        void DestroyTexture(int id) override;

        void SetTextureData(int id, int mipmap, const void* data) override;

        Vector2 GetTextureSize(int id) const override;

        int GetWhiteTexture() override;

        int CreateMesh(int vertexCount, int indexCount) override;

        void DestroyMesh(int id) override;

        void SetMeshData(int id, const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices) override;

        int CreateInstance() override;

        void DestroyInstance(int id) override;

        void SetInstanceTransform(int id, const Matrix4& transform) override;

        void SetInstanceMesh(int id, int meshId) override;

        void SetInstanceViewport(int id, int viewportId) override;

        int CreateCanvasItem() override;

        void DestroyCanvasItem(int id) override;

        void SetCanvasItemData(int id, const ArrayView<const Vertex2D>& vertices, const ArrayView<const int>& indices) override;

        void SetCanvasItemTexture(int id, int textureId) override;

        void DrawCanvasItem(int id, int vertexOffset, int indexOffset, int indexCount) override;

        void Render() override;

    public:
        void LLSetVertexBufferData2D(const ArrayView<const Vertex2D>& vertices) override;

        void LLSetIndexBufferData2D(const ArrayView<const unsigned short>& indices) override;

        void LLSetTexture2D(int textureId) override;

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
            int ColorTextureId = 0;
            int DepthTextureId = 0;
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

        int mWhiteTextureId = Pool::None;
    };
}
