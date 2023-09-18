#pragma once 

#include "Node.hpp"

namespace YAWN {
    class Scene {
    public:
        static void Initialize();

        static void Release();

        static void Update(float timeStep);

        static void LateUpdate(float timeStep);

        static void FixedUpdate(float timeStep);

        static const Ref<Node>& GetRoot();

    private:
        static void Update(const Ref<Node>& node, float timeStep);

        static void LateUpdate(const Ref<Node>& node, float timeStep);

        static void FixedUpdate(const Ref<Node>& node, float timeStep);

    private:
        static Ref<Node> sRoot;
    };
}
