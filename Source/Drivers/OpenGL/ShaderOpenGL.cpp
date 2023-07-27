#include "ShaderOpenGL.hpp"

#include <stdio.h>

using namespace YAWN;

static GLenum TranslateShaderType(ShaderType type) {
    switch (type) {
    case ShaderType::Vertex:
        return GL_VERTEX_SHADER;
    case ShaderType::Fragment:
        return GL_FRAGMENT_SHADER;
    case ShaderType::Compute:
        return GL_COMPUTE_SHADER;
    }

    return GL_VERTEX_SHADER;
}

ShaderOpenGL::ShaderOpenGL(ShaderType type, const String& code)
    : Shader(type, code), mNativeType(TranslateShaderType(type)) {
    Array<char> utf8 = code.ToUTF8();

    const char* codes[] = { utf8.GetData() };
    mId = glCreateShaderProgramv(mNativeType, 1, codes);

#ifdef _DEBUG
    GLint result, infoLength;
    glGetProgramiv(mId, GL_LINK_STATUS, &result);
    glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &infoLength);
    if (!result && infoLength > 0) {
        Array<char> message(infoLength + 1);
        glGetProgramInfoLog(mId, infoLength, nullptr, &message[0]);
        message[infoLength] = 0;

        printf("%s\n", message.GetData());
    }
#endif
}

ShaderOpenGL::~ShaderOpenGL() {
    glDeleteShader(mId);
}

GLuint ShaderOpenGL::GetId() const {
    return mId;
}
