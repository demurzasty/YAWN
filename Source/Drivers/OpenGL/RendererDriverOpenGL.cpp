#include "RendererDriverOpenGL.hpp"

#include <YAWN/Runtime/Console.hpp>

#include "Shaders/Generated/Culling.comp.h"
#include "Shaders/Generated/Forward.vert.h"
#include "Shaders/Generated/Forward.frag.h"

#include <stddef.h> // offsetof

using namespace YAWN;

RendererDriverOpenGL::RendererDriverOpenGL() {
    YAWN_GL_CHECK(glCreateBuffers(1, &mGlobalBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mGlobalBufferId, sizeof(GPUGlobalData), nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT));

    YAWN_GL_CHECK(glCreateBuffers(1, &mInstanceBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mInstanceBufferId, sizeof(GPUInstanceData) * MaxInstanceCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT));

    YAWN_GL_CHECK(glCreateBuffers(1, &mMeshBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mMeshBufferId, sizeof(GPUMeshData) * MaxMeshCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT));

    YAWN_GL_CHECK(glCreateBuffers(1, &mSamplerBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mSamplerBufferId, sizeof(GLuint64) * MaxTextureCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT));

    YAWN_GL_CHECK(glCreateBuffers(1, &mDrawBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mDrawBufferId, sizeof(GPUDrawElementsIndirectCommand) * MaxInstanceCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT));

    YAWN_GL_CHECK(glCreateBuffers(1, &mVertexBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mVertexBufferId, sizeof(Vertex3D) * MaxVertexCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT));

    YAWN_GL_CHECK(glCreateBuffers(1, &mIndexBufferId));
    YAWN_GL_CHECK(glNamedBufferStorage(mIndexBufferId, sizeof(unsigned int) * MaxIndexCount, nullptr, GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT));

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

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, mGlobalBufferId);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, mInstanceBufferId);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, mMeshBufferId);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, mSamplerBufferId);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, mDrawBufferId);

    mCullingProgramId = CompileShader(Culling_comp);
    mForwardProgramId = CompileShader(Forward_vert, Forward_frag);

    YAWN_GL_CHECK(glPixelStorei(GL_PACK_ALIGNMENT, 1));
    YAWN_GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

    mGlobalData = (GPUGlobalData*)glMapNamedBuffer(mGlobalBufferId, GL_READ_WRITE);
    mInstances = (GPUInstanceData*)glMapNamedBuffer(mInstanceBufferId, GL_READ_WRITE);
    mMeshes = (GPUMeshData*)glMapNamedBuffer(mMeshBufferId, GL_READ_WRITE);
    mSamplers = (GLuint64*)glMapNamedBuffer(mSamplerBufferId, GL_READ_WRITE);
    mVertices = (Vertex3D*)glMapNamedBuffer(mVertexBufferId, GL_READ_WRITE);
    mIndices = (GLint*)glMapNamedBuffer(mIndexBufferId, GL_READ_WRITE);
}

RendererDriverOpenGL::~RendererDriverOpenGL() {
    glUnmapNamedBuffer(mIndexBufferId);
    glUnmapNamedBuffer(mVertexBufferId);
    glUnmapNamedBuffer(mSamplerBufferId);
    glUnmapNamedBuffer(mMeshBufferId);
    glUnmapNamedBuffer(mInstanceBufferId);
    glUnmapNamedBuffer(mGlobalBufferId);

    YAWN_GL_CHECK(glDeleteProgramPipelines(1, &mForwardProgramId));
    YAWN_GL_CHECK(glDeleteProgramPipelines(1, &mCullingProgramId));

    YAWN_GL_CHECK(glDeleteVertexArrays(1, &mVertexArrayObjectId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mIndexBufferId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mVertexBufferId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mDrawBufferId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mSamplerBufferId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mMeshBufferId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mInstanceBufferId));
    YAWN_GL_CHECK(glDeleteBuffers(1, &mGlobalBufferId));
}

void RendererDriverOpenGL::SetCameraProjection(const Matrix4& projection) {
    mGlobalData->Projection = projection;
}

void RendererDriverOpenGL::SetCameraTransform(const Matrix4& transform) {
    mGlobalData->View = Matrix4::Invert(transform);
    mGlobalData->CameraPosition = Vector4(Matrix4::ExtractPosition(transform), 1.0f);
}

int RendererDriverOpenGL::CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount) {
    int id = RendererDriver::CreateTexture(width, height, format, filter, wrapping, mipmapCount);

    return id;
}

void RendererDriverOpenGL::DestroyTexture(int id) {
    RendererDriver::DestroyTexture(id);
}

int RendererDriverOpenGL::CreateMesh(int vertexCount, int indexCount) {
    int id = RendererDriver::CreateMesh(vertexCount, indexCount);

    return id;
}

void RendererDriverOpenGL::DestroyMesh(int id) {
    RendererDriver::DestroyMesh(id);
}

int RendererDriverOpenGL::CreateInstance() {
    int id = RendererDriver::CreateInstance();

    mInstances[id] = GPUInstanceData();

    return id;
}

void RendererDriverOpenGL::DestroyInstance(int id) {
    RendererDriver::DestroyInstance(id);
}

void RendererDriverOpenGL::SetInstanceTransform(int id, const Matrix4& transform) {
    mInstances[id].Transform = transform;
}

void RendererDriverOpenGL::Present() {
    mGlobalData->ProjectionView = mGlobalData->Projection * mGlobalData->View;
    mGlobalData->InvertedProjectionView = Matrix4::Invert(mGlobalData->ProjectionView);
    mGlobalData->CameraPosition = Vector4(0.0f, 0.0f, 10.0f, 0.0f);
    mGlobalData->InstanceCount = mInstancePool.GetSize();

    YAWN_GL_CHECK(glClearColor(mClearColor.R, mClearColor.G, mClearColor.B, mClearColor.A));
    YAWN_GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    YAWN_GL_CHECK(glBindProgramPipeline(mCullingProgramId));

    YAWN_GL_CHECK(glDispatchCompute(Math::Align(mGlobalData->InstanceCount, 64) / 64, 1, 1));

    YAWN_GL_CHECK(glBindProgramPipeline(mForwardProgramId));

    YAWN_GL_CHECK(glBindVertexArray(mVertexArrayObjectId));

    YAWN_GL_CHECK(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, mDrawBufferId));

    YAWN_GL_CHECK(glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, mGlobalData->InstanceCount, sizeof(GPUDrawElementsIndirectCommand)));
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

        Console::WriteLine(L"%s", message.GetData());
    }
}

void RendererDriverOpenGL::CheckError(const wchar_t* path, int line, const wchar_t* expression) {
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
