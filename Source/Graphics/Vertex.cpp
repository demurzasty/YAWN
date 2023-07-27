#include <YAWN/Graphics/Vertex.hpp>

using namespace YAWN;

Vertex3D::Vertex3D(const Vector3& position, const Vector2& uv, const Vector3& normal)
    : Position(position), UV(uv), Normal(normal) {
}
