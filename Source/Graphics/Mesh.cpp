#include <YAWN/Graphics/Mesh.hpp>
#include <YAWN/Graphics/Renderer.hpp>

using namespace YAWN;

Ref<Mesh> Mesh::CreateBox(const Vector3& extent) {
    Ref<Mesh> mesh = new Mesh(24, 36);

    Vertex3D vertices[24] = {
        Vertex3D(Vector3(-extent.X, extent.Y, extent.Z), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)),
        Vertex3D(Vector3(-extent.X, -extent.Y, extent.Z), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)),
        Vertex3D(Vector3(extent.X, -extent.Y, extent.Z), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)),
        Vertex3D(Vector3(extent.X, extent.Y, extent.Z), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)),

        Vertex3D(Vector3(extent.X, extent.Y, extent.Z), Vector2(0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)),
        Vertex3D(Vector3(extent.X, -extent.Y, extent.Z), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)),
        Vertex3D(Vector3(extent.X, -extent.Y, -extent.Z), Vector2(1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)),
        Vertex3D(Vector3(extent.X, extent.Y, -extent.Z), Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)),

        Vertex3D(Vector3(extent.X, extent.Y, -extent.Z), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)),
        Vertex3D(Vector3(extent.X, -extent.Y, -extent.Z), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)),
        Vertex3D(Vector3(-extent.X, -extent.Y, -extent.Z), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)),
        Vertex3D(Vector3(-extent.X, extent.Y, -extent.Z), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)),

        Vertex3D(Vector3(-extent.X, extent.Y, -extent.Z), Vector2(0.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)),
        Vertex3D(Vector3(-extent.X, -extent.Y, -extent.Z), Vector2(0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)),
        Vertex3D(Vector3(-extent.X, -extent.Y, extent.Z), Vector2(1.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)),
        Vertex3D(Vector3(-extent.X, extent.Y, extent.Z), Vector2(1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)),

        Vertex3D(Vector3(-extent.X, extent.Y, -extent.Z), Vector2(0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)),
        Vertex3D(Vector3(-extent.X, extent.Y, extent.Z), Vector2(0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f)),
        Vertex3D(Vector3(extent.X, extent.Y, extent.Z), Vector2(1.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f)),
        Vertex3D(Vector3(extent.X, extent.Y, -extent.Z), Vector2(1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)),

        Vertex3D(Vector3(-extent.X, -extent.Y, extent.Z), Vector2(0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)),
        Vertex3D(Vector3(-extent.X, -extent.Y, -extent.Z), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)),
        Vertex3D(Vector3(extent.X, -extent.Y, -extent.Z), Vector2(1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)),
        Vertex3D(Vector3(extent.X, -extent.Y, extent.Z), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)),
    };

    int indices[36] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    mesh->SetData(vertices, indices);
    return mesh;
}

Mesh::Mesh(int vertexCount, int indexCount)
    : mId(Renderer::CreateMesh(vertexCount, indexCount)) {
}

Mesh::~Mesh() {
    Renderer::DestroyMesh(mId);
}

void Mesh::SetData(const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices) {
    Renderer::SetMeshData(mId, vertices, indices);
}
