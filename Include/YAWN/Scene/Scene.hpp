#pragma once 

#include "Viewport.hpp"

namespace YAWN {
    class Scene {
    public:
        static void Initialize();

        static void Release();

        static void Update(float timeStep);

        static void LateUpdate(float timeStep);

        static void FixedUpdate(float timeStep);

        static void HandleEvent(const Event& event);

        static void Redraw();

        static const Ref<Viewport>& GetRoot();

    private:
        static void Update(const Ref<Node>& node, float timeStep);

        static void LateUpdate(const Ref<Node>& node, float timeStep);

        static void FixedUpdate(const Ref<Node>& node, float timeStep);

        static void HandleEvent(const Ref<Node>& node, const Event& event);

        static void Redraw(const Ref<Node>& node);

    private:
        static Ref<Viewport> sRoot;
    };
}
