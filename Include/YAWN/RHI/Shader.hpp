#pragma once

#include "../Runtime/Reference.hpp"
#include "../Core/String.hpp"

namespace YAWN {
    enum class ShaderType {
        Vertex,
        Fragment,
        Compute
    };

    class Shader : public Reference {
        YAWN_OBJECT(Shader, Reference);

    public:
        virtual ~Shader() = default;

        ShaderType GetType() const;

    protected:
        Shader(ShaderType type, const String& code);

    private:
        const ShaderType mType;
    };
}