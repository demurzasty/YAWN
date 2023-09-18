#pragma once 

#include "Node.hpp"
#include "../Core/ArrayView.hpp"

namespace YAWN {
    class Node3D : public Node {
        YAWN_OBJECT(Node3D, Reactive);

    public:
        static void Register(Meta<Node3D>& meta);

    public:
        virtual ~Node3D();

        //////////////////////////
        /////// Frame Loop ///////
        //////////////////////////

        void Update(float timeStep);

        void LateUpdate(float timeStep);

        void FixedUpdate(float timeStep);

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

    protected:
        //////////////////////////
        ///////// Events /////////
        //////////////////////////

        virtual void OnTransformUpdate();

        virtual void OnVectorsUpdate();

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

        mutable int mDirty = TransformDirtyFlags::Notify;
    };
}
