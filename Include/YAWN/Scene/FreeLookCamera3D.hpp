#pragma once 

#include "Camera3D.hpp"

namespace YAWN {
    class FreeLookCamera3D : public Camera3D {
        YAWN_OBJECT(FreeLookCamera3D, Camera3D);

    public:
        static void Register(Meta<FreeLookCamera3D>& meta);

    public:
        virtual ~FreeLookCamera3D() = default;

        virtual void Enter() override;

        virtual void Update(float timeStep) override;

    private:
        Vector3 Smooth(const Vector3& origin, const Vector3& target, float timeStep);

    private:
        Vector2 mLastMousePosition = Vector2::Zero;
        Vector3 mTargetCameraPosition = Vector3::Zero;
        Vector3 mTargetCameraRotation = Vector3::Zero;
    };
}
