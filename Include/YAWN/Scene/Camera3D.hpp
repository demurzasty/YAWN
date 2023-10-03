#pragma once 

#include "Node3D.hpp"

namespace YAWN {
    class Camera3D : public Node3D {
        YAWN_OBJECT(Camera3D, Node3D);

    public:
        static void Register(Meta<Camera3D>& meta);

    public:
        virtual ~Camera3D() = default;

        virtual void Enter() override;

        virtual void Exit() override;

        virtual void Update(float timeStep) override;

        virtual void HandleEvent(const Event& event) override;

    private:
        virtual void OnTransformUpdate() override;
    };
}
