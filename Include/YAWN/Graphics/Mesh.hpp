#pragma once 

#include "../Runtime/Resource.hpp"
#include "Vertex.hpp"

namespace YAWN {
    class Mesh : public Resource {
        YAWN_OBJECT(Mesh, Resource);

    public:
        static void Register(Meta<Mesh>& meta);

        static Ref<Mesh> CreateBox(const Vector3& extent);

        Mesh(int vertexCount, int indexCount);

        virtual ~Mesh() override;

        void SetData(const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices);

        int GetId() const;

    private:
        const int mId;
    };
}