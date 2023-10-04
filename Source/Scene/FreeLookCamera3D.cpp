#include <YAWN/Scene/FreeLookCamera3D.hpp>
#include <YAWN/Platform/Input.hpp>
#include <YAWN/Platform/Window.hpp>

using namespace YAWN;

void FreeLookCamera3D::Register(Meta<FreeLookCamera3D>& meta) {
    meta.SetConstructable();
}

void FreeLookCamera3D::Enter() {
    Base::Enter();

    mLastMousePosition = Input::GetMousePosition();
    mTargetCameraRotation = GetLocalRotation();
    mTargetCameraPosition = GetLocalPosition();
}

void FreeLookCamera3D::Update(float timeStep) {
    Base::Update(timeStep);

    if (Input::IsMouseButtonPressed(MouseButton::Right)) {
        mLastMousePosition = Input::GetMousePosition();
    }

    if (Input::IsMouseButtonDown(MouseButton::Right)) {
        const float speed = Input::IsKeyDown(Key::Space) ? 10.0f : 2.5f;

        const Vector2 mousePosition = Input::GetMousePosition();
        const Vector2 diff = mLastMousePosition - mousePosition;
        mLastMousePosition = mousePosition;

        mTargetCameraRotation.Y += diff.X * 0.005f;
        mTargetCameraRotation.X += diff.Y * 0.005f;

        if (Input::IsKeyDown(Key::E)) {
            mTargetCameraPosition.Y += timeStep * speed;
        } else if (Input::IsKeyDown(Key::Q)) {
            mTargetCameraPosition.Y -= timeStep * speed;
        }

        if (Input::IsKeyDown(Key::W)) {
            mTargetCameraPosition.X -= Math::Sin(mTargetCameraRotation.Y) * timeStep * speed;
            mTargetCameraPosition.Z -= Math::Cos(mTargetCameraRotation.Y) * timeStep * speed;
        } else if (Input::IsKeyDown(Key::S)) {
            mTargetCameraPosition.X += Math::Sin(mTargetCameraRotation.Y) * timeStep * speed;
            mTargetCameraPosition.Z += Math::Cos(mTargetCameraRotation.Y) * timeStep * speed;
        }

        if (Input::IsKeyDown(Key::D)) {
            mTargetCameraPosition.X -= Math::Sin(mTargetCameraRotation.Y - Math::PI * 0.5f) * timeStep * speed;
            mTargetCameraPosition.Z -= Math::Cos(mTargetCameraRotation.Y - Math::PI * 0.5f) * timeStep * speed;
        } else if (Input::IsKeyDown(Key::A)) {
            mTargetCameraPosition.X -= Math::Sin(mTargetCameraRotation.Y + Math::PI * 0.5f) * timeStep * speed;
            mTargetCameraPosition.Z -= Math::Cos(mTargetCameraRotation.Y + Math::PI * 0.5f) * timeStep * speed;
        }

        Window::Invalidate();
    }

    SetLocalPosition(mTargetCameraPosition);
    SetLocalRotation(mTargetCameraRotation);
}
