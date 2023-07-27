#pragma once

#include "../Runtime/Resource.hpp"
#include "../Core/String.hpp"

namespace YAWN {
    enum class ShaderType {
        Vertex,
        Fragment,
        Compute
    };

    class Shader : public Resource {
        YAWN_OBJECT(Shader, Resource);

    public:
        virtual ~Shader() = default;

        ShaderType GetType() const;

    protected:
        Shader(ShaderType type, const String& code);

    private:
        const ShaderType mType;
    };
}