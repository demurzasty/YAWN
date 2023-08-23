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

        struct GPUDrawElementsIndirectCommand {
            int IndexCount = 0;
            int InstanceCount = 0;
            int IndexOffset = 0;
            int VertexOffset = 0;
            int FirstInstance = 0;
        };

    public:
        RendererDriverOpenGL();

        ~RendererDriverOpenGL() override;

        void SetCameraProjection(const Matrix4& projection) override;

        void SetCameraTransform(const Matrix4& transform) override;

        int CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount) override;

        void DestroyTexture(int id) override;

        int CreateMesh(int vertexCount, int indexCount) override;

        void DestroyMesh(int id) override;

        int CreateInstance() override;

        void DestroyInstance(int id) override;

        void SetInstanceTransform(int id, const Matrix4& transform) override;

        void Present() override;

    private:
        GLuint CompileShader(ArrayView<const char> vertexCode, ArrayView<const char> fragmentCode);

        GLuint CompileShader(ArrayView<const char> computeCode);

        void TestShader(GLuint shaderProgram);

        void CheckError(const wchar_t* path, int line, const wchar_t* expression);

    private:
        GLuint mGlobalBufferId = 0;
        GLuint mInstanceBufferId = 0;
        GLuint mMeshBufferId = 0;
        GLuint mSamplerBufferId = 0;
        GLuint mDrawBufferId = 0;
        GLuint mVertexBufferId = 0;
        GLuint mIndexBufferId = 0;
        GLuint mVertexArrayObjectId = 0;

        GLuint mCullingProgramId = 0;
        GLuint mForwardProgramId = 0;

        GPUGlobalData* mGlobalData = nullptr;
        GPUInstanceData* mInstances = nullptr;
        GPUMeshData* mMeshes = nullptr;
        GLuint64* mSamplers = nullptr;
        Vertex3D* mVertices = nullptr;
        GLint* mIndices = nullptr;

        int mGlobalVertexOffset = 0;
        int mGlobalIndexOffset = 0;
    };
}
