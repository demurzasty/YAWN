#pragma once 

#include "../Component.hpp"

namespace YAWN {
    class Camera : public Component {
        YAWN_OBJECT(Camera, Component);

    public:
        static void Register(Meta<Camera>& meta);

    public:
        virtual ~Camera() = default;

        virtual void Enter() override;

        virtual void Exit() override;

    private:
        void OnTransformUpdate(const Ref<Actor>& actor);
    };
}
