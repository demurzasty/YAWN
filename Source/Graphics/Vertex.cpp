#include <YAWN/Graphics/Vertex.hpp>

using namespace YAWN;

Vertex2D::Vertex2D(const Vector2& position, const Vector2& uv, const YAWN::Color& color)
    : Position(position), UV(uv), Color(color) {
}

Vertex3D::Vertex3D(const Vector3& position, const Vector2& uv, const Vector3& normal)
    : Position(position), UV(uv), Normal(normal) {
}
