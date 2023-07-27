#pragma once 

#include <YAWN/RHI/Shader.hpp>

#include <GL/glew.h>

namespace YAWN {
    class ShaderOpenGL : public Shader {
        YAWN_OBJECT(ShaderOpenGL, Shader);

    public:
        ShaderOpenGL(ShaderType type, const String& code);

        ~ShaderOpenGL() override;

        GLuint GetId() const;

    private:
        const GLenum mNativeType;
        GLuint mId = 0;
    };
}