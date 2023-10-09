#include <YAWN/Scene/Gizmo3D.hpp>

using namespace YAWN;

void Gizmo3D::Register(Meta<Gizmo3D>& meta) {
}

Gizmo3D::Gizmo3D() {
    int resolution = 36;
    float radius = 0.30f;
    float height = 1.0f;

    Array<Vertex3D> vertices;
    for (int i = 0; i < resolution; ++i) {
        float ration = float(i) / resolution;
        float r = ration * Math::TAU;
        float x = Math::Cos(r) * radius;
        float y = Math::Sin(r) * radius;

        vertices.Add(Vertex3D(Vector3(x, y, 0.0f), Vector2::Zero, Vector3::Zero));
    }

    vertices.Add(Vertex3D(Vector3(0.0f, 0.0f, height), Vector2::Zero, Vector3::Zero));

    Array<int> indices;
    for (int i = 0; i < resolution; ++i) {
        int ii = (i + 1) % resolution;

        indices.Add(vertices.GetSize() - 1);
        indices.Add(i);
        indices.Add(ii);
    }

    Ref<Mesh> mesh = new Mesh(vertices.GetSize(), indices.GetSize());
    mesh->SetData(vertices, indices);
    SetMesh(mesh);
}
