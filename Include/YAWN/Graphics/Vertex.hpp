#pragma once 

#include "../Math/Vector2.hpp"
#include "../Math/Vector3.hpp"

namespace YAWN {
    struct Vertex3D {
        Vertex3D() = default;

        Vertex3D(const Vector3& position, const Vector2& uv, const Vector3& normal);

        Vector3 Position;
        Vector2 UV;
        Vector3 Normal;
    };
}
