#pragma once 

#include "../Component.hpp"
#include "../../Runtime/Pool.hpp"
#include "../../Graphics/Mesh.hpp"

namespace YAWN {
    class Geometry : public Component {
        YAWN_OBJECT(Geometry, Component);

    public:
        static void Register(Meta<Geometry>& meta);

    public:
        virtual ~Geometry() = default;

        virtual void Enter() override;

        virtual void Exit() override;

        void SetMesh(const Ref<Mesh>& mesh);

        const Ref<Mesh>& GetMesh() const;

    private:
        void OnTransformUpdate(const Ref<Actor>& actor);

    private:
        int mId = Pool::None;

        Ref<Mesh> mMesh;
    };
}