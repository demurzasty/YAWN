#pragma once 

#include "../Runtime/Resource.hpp"
#include "Vertex.hpp"

namespace YAWN {
    class Mesh : public Resource {
        YAWN_OBJECT(Mesh, Resource);

    public:
        static void Register(Meta<Mesh>& meta);

        static Ref<Mesh> CreateBox(const Vector3& extent);

        static Ref<Mesh> CreatePlane(const Vector2& size, const Vector2& uvScale);

        Mesh(int vertexCount, int indexCount);

        virtual ~Mesh() override;

        void SetData(const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices);

        OID GetId() const;

    private:
        const OID mId;
    };
}