#pragma once 

#include "../Runtime/Reactive.hpp"
#include "../Reflection/Meta.hpp"

namespace YAWN {
    class Actor;

    class Component : public Reactive {
        YAWN_OBJECT(Component, Reactive);

        friend class Actor;

    public:
        static void Register(Meta<Component>& meta);

    public:
        virtual ~Component() = default;

        virtual void Enter();

        virtual void Exit();

        virtual void Update(float timeStep);

        virtual void LateUpdate(float timeStep);

        virtual void FixedUpdate(float timeStep);

        Actor* GetOwner() const;

    private:
        Actor* mOwner = nullptr;
    };
}