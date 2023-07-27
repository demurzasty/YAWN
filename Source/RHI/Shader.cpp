#include <YAWN/RHI/Shader.hpp>

using namespace YAWN;

ShaderType Shader::GetType() const {
    return mType;
}

Shader::Shader(ShaderType type, const String& code)
    : mType(type) {
}
