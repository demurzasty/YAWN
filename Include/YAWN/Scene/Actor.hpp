#pragma once 

#include "Component.hpp"
#include "../Core/ArrayView.hpp"
#include "../Math/Matrix4.hpp"
#include "../Runtime/Signal.hpp"

namespace YAWN {
    class Actor : public Reactive {
        YAWN_OBJECT(Actor, Reactive);

    public:
        static void Register(Meta<Actor>& meta);

    public:
        virtual ~Actor();

        //////////////////////////
        /////// Components ///////
        //////////////////////////

        void AddComponent(const Ref<Component>& component);

        bool HasComponent(int typeId);

        Ref<Component> GetComponent(int typeId);

        template<typename TComponent>
        Ref<TComponent> AddComponent() {
            Ref<TComponent> component = new TComponent();
            AddComponent(component);
            return component;
        }

        template<typename TComponent>
        bool HasComponent() {
            return HasComponent(TypeID::Hash<TComponent>());
        }

        template<typename... TComponents>
        bool HasComponents() {
            return (HasComponent(TypeID::Hash<TComponents>()) && ...);
        }

        template<typename TComponent>
        Ref<TComponent> GetComponent() {
            return CastTo<TComponent>(GetComponent(TypeID::Hash<TComponent>()));
        }

        //////////////////////////
        /////// Frame Loop ///////
        //////////////////////////

        void Update(float timeStep);

        void LateUpdate(float timeStep);

        void FixedUpdate(float timeStep);

        //////////////////////////
        ///////// Basic //////////
        //////////////////////////

        void SetName(const String& name);

        const String& GetName() const;

        //////////////////////////
        /////// Hierarchy ////////
        //////////////////////////

        Actor* GetParent() const;

        void AddChild(const Ref<Actor>& node);

        void AddSibling(const Ref<Actor>& node);

        ArrayView<const Ref<Actor>> GetChildren() const;

        //////////////////////////
        ///////// Local //////////
        //////////////////////////

        void SetLocalPosition(const Vector3& position);

        const Vector3& GetLocalPosition() const;

        void SetLocalRotation(const Vector3& rotation);

        const Vector3& GetLocalRotation() const;

        void SetLocalScale(const Vector3& scale);

        const Vector3& GetLocalScale() const;

        void SetLocalTransform(const Matrix4& transform);

        const Matrix4& GetLocalTransform() const;

        //////////////////////////
        ///////// Global /////////
        //////////////////////////

        Vector3 GetGlobalPosition() const;

        Vector3 GetGlobalRotation() const;

        void SetGlobalTransform(const Matrix4& transform, bool notify = true);

        const Matrix4& GetGlobalTransform() const;

        //////////////////////////
        //////// Signals /////////
        //////////////////////////

        Signal<const Ref<Actor>&>& GetTransformUpdateSignal();

        Signal<const Ref<Actor>&>& GetVectorsUpdateSignal();

    private:
        void UpdateLocalVectors() const;

    private:
        struct TransformDirtyFlags {
            static constexpr int None = 0;

            static constexpr int LocalVectors = 1;

            static constexpr int LocalTransform = 2;
            static constexpr int GlobalTransform = 4;

            static constexpr int NotifyTransform = 8;
            static constexpr int NotifyVectors = 16;

            static constexpr int All = LocalVectors | LocalTransform | GlobalTransform | NotifyTransform | NotifyVectors;
            static constexpr int Notify = NotifyTransform | NotifyVectors;
        };

    private:
        //////////////////////////
        ///////// Basic //////////
        //////////////////////////

        String mName;

        //////////////////////////
        /////// Hierarchy ////////
        //////////////////////////

        Actor* mParent = nullptr;
        Array<Ref<Actor>> mChildren;

        //////////////////////////
        /////// Components ///////
        //////////////////////////

        Map<int, Ref<Component>> mComponents;

        //////////////////////////
        ///////// Local //////////
        //////////////////////////

        mutable Vector3 mLocalPosition = Vector3::Zero;
        mutable Vector3 mLocalRotation = Vector3::Zero;
        mutable Vector3 mLocalScale = Vector3::One;
        mutable Matrix4 mLocalTransform = Matrix4::Identity;

        //////////////////////////
        ///////// Global /////////
        //////////////////////////

        mutable Matrix4 mGlobalTransform = Matrix4::Identity;

        //////////////////////////
        ////////// State /////////
        //////////////////////////

        mutable int mDirty = TransformDirtyFlags::None;

        //////////////////////////
        //////// Signals /////////
        //////////////////////////
        
        Signal<const Ref<Actor>&> mTransformUpdateSignal;
        Signal<const Ref<Actor>&> mVectorsUpdateSignal;
    };
}
