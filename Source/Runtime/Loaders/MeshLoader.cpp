#include <YAWN/Runtime/Loaders/MeshLoader.hpp>
#include <YAWN/Graphics/Mesh.hpp>
#include <YAWN/IO/File.hpp>

using namespace YAWN;

void MeshLoader::Register(Meta<MeshLoader>& meta) {
    meta.SetBase<Loader>();
    meta.SetName(L"MeshLoader");
    meta.SetConstructable();
}

Ref<Resource> MeshLoader::Load(const Path& path) {
    File file;
    file.Open(path, FileModeFlags::Read);

    YAWN_ASSERT(file.IsOpen());

    int vertexCount = file.Read32();
    int indexCount = file.Read32();

    Array<Vertex3D> vertices(vertexCount);
    Array<int> indices(indexCount);

    file.Read(vertices.GetData(), vertices.GetSizeInBytes());
    file.Read(indices.GetData(), indices.GetSizeInBytes());

    Ref<Mesh> mesh = new Mesh(vertexCount, indexCount);

    mesh->SetData(vertices, indices);

    return mesh;
}

int MeshLoader::GetSupportedResourceTypeId() const {
    return TypeID::Hash<Mesh>();
}
