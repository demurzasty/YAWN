#pragma once 

#include "Node3D.hpp"
#include "../Graphics/Mesh.hpp"
#include "../Graphics/Material.hpp"
#include "../Runtime/Pool.hpp"

namespace YAWN {
    class Geometry3D : public Node3D {
        YAWN_OBJECT(Geometry3D, Node3D);

    public:
        static void Register(Meta<Geometry3D>& meta);

    public:
        virtual ~Geometry3D() = default;

        void SetMesh(const Ref<Mesh>& mesh);

        const Ref<Mesh>& GetMesh() const;

        void SetMaterial(const Ref<Material>& material);

        const Ref<Material>& GetMaterial() const;

    protected:
        virtual void Enter() override;

        virtual void Exit() override;

    private:
        virtual void OnTransformUpdate() override;

    private:
        int mId = Pool::None;
        Ref<Mesh> mMesh;
        Ref<Material> mMaterial;
    };
}
