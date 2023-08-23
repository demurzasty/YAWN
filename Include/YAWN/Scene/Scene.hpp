#pragma once 

#include "Actor.hpp"

namespace YAWN {
    class Scene {
    public:
        static void Initialize();

        static void Release();

        static void Update(float timeStep);

        static void LateUpdate(float timeStep);

        static void FixedUpdate(float timeStep);

        static const Ref<Actor>& GetRoot();

    private:
        static void Update(const Ref<Actor>& actor, float timeStep);

        static void LateUpdate(const Ref<Actor>& actor, float timeStep);

        static void FixedUpdate(const Ref<Actor>& actor, float timeStep);

    private:
        static Ref<Actor> sRoot;
    };
}
