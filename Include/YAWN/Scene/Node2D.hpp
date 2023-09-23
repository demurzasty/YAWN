#pragma once 

#include "Node.hpp"
#include "../Math/Matrix3.hpp"
#include "../Core/ArrayView.hpp"

namespace YAWN {
    class Node2D : public Node {
        YAWN_OBJECT(Node2D, Node);

    public:
        static void Register(Meta<Node2D>& meta);

    public:
        virtual ~Node2D();

        //////////////////////////
        /////// Frame Loop ///////
        //////////////////////////

        void Update(float timeStep) override;

        void LateUpdate(float timeStep) override;

        void FixedUpdate(float timeStep) override;

        void Draw() override;

        //////////////////////////
        ///////// Local //////////
        //////////////////////////

        void SetLocalPosition(const Vector2& position);

        const Vector2& GetLocalPosition() const;

        void SetLocalRotation(float rotation);

        float GetLocalRotation() const;

        void SetLocalScale(const Vector2& scale);

        const Vector2& GetLocalScale() const;

        void SetLocalTransform(const Matrix3& transform);

        const Matrix3& GetLocalTransform() const;

        //////////////////////////
        ///////// Global /////////
        //////////////////////////

        Vector2 GetGlobalPosition() const;

        float GetGlobalRotation() const;

        void SetGlobalTransform(const Matrix3& transform, bool notify = true);

        const Matrix3& GetGlobalTransform() const;

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

        mutable Vector2 mLocalPosition = Vector2::Zero;
        mutable float mLocalRotation = 0.0f;
        mutable Vector2 mLocalScale = Vector2::One;
        mutable Matrix3 mLocalTransform = Matrix3::Identity;

        //////////////////////////
        ///////// Global /////////
        //////////////////////////

        mutable Matrix3 mGlobalTransform = Matrix3::Identity;

        //////////////////////////
        ////////// State /////////
        //////////////////////////

        mutable int mDirty = TransformDirtyFlags::Notify;
    };
}
