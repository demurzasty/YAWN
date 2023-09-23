#include <YAWN/Scene/Node2D.hpp>
#include <YAWN/Graphics/Renderer.hpp>

#include <stdio.h>

using namespace YAWN;

void Node2D::Register(Meta<Node2D>& meta) {
    meta.SetBase<Node>();
    meta.SetName(L"Node2D");
    meta.SetConstructable();
    meta.AddField<&Node2D::SetLocalPosition, &Node2D::GetLocalPosition>(L"Position");
    meta.AddField<&Node2D::SetLocalRotation, &Node2D::GetLocalRotation>(L"Rotation");
    meta.AddField<&Node2D::SetLocalScale, &Node2D::GetLocalScale>(L"Scale");
}

Node2D::~Node2D() {
}

void Node2D::Update(float timeStep) {
}

void Node2D::LateUpdate(float timeStep) {
    if (mDirty & TransformDirtyFlags::NotifyTransform) {
        for (const Ref<Node>& node : GetChildren()) {
            if (node->IsInstanceOf<Node2D>()) {
                CastTo<Node2D>(node)->mDirty |= TransformDirtyFlags::All;
            }
        }

        OnTransformUpdate();

        mDirty &= ~TransformDirtyFlags::NotifyTransform;
    }

    if (mDirty & TransformDirtyFlags::NotifyVectors) {
        OnVectorsUpdate();

        mDirty &= ~TransformDirtyFlags::NotifyVectors;
    }
}

void Node2D::FixedUpdate(float timeStep) {
}

void Node2D::Draw() {
}

void Node2D::SetLocalPosition(const Vector2& position) {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    mLocalPosition = position;
    mDirty |= TransformDirtyFlags::LocalTransform | TransformDirtyFlags::GlobalTransform | TransformDirtyFlags::Notify;
}

const Vector2& Node2D::GetLocalPosition() const {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    return mLocalPosition;
}

void Node2D::SetLocalRotation(float rotation) {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    mLocalRotation = rotation;
    mDirty |= TransformDirtyFlags::LocalTransform | TransformDirtyFlags::GlobalTransform | TransformDirtyFlags::Notify;
}

float Node2D::GetLocalRotation() const {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    return mLocalRotation;
}

void Node2D::SetLocalScale(const Vector2& scale) {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    mLocalScale = scale;
    mDirty |= TransformDirtyFlags::LocalTransform | TransformDirtyFlags::GlobalTransform | TransformDirtyFlags::Notify;
}

const Vector2& Node2D::GetLocalScale() const {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    return mLocalScale;
}

void Node2D::SetLocalTransform(const Matrix3& transform) {
    mLocalTransform = transform;
    mDirty |= TransformDirtyFlags::LocalVectors | TransformDirtyFlags::GlobalTransform | TransformDirtyFlags::NotifyTransform;
    mDirty &= ~TransformDirtyFlags::LocalTransform;
}

const Matrix3& Node2D::GetLocalTransform() const {
    if (mDirty & TransformDirtyFlags::LocalTransform) {
        mLocalTransform = Matrix3::CreateTranslation2D(mLocalPosition) *
            Matrix3::CreateRotation2D(mLocalRotation) *
            Matrix3::CreateScaling2D(mLocalScale);

        mDirty &= ~TransformDirtyFlags::LocalTransform;
    }

    return mLocalTransform;
}

Vector2 Node2D::GetGlobalPosition() const {
    return Matrix3::ExtractPosition2D(GetGlobalTransform());
}

float Node2D::GetGlobalRotation() const {
    return Matrix3::ExtractEuler2D(GetGlobalTransform());
}

void Node2D::SetGlobalTransform(const Matrix3& transform, bool notify) {
    if (GetParent() && GetParent()->IsInstanceOf<Node2D>()) {
        mLocalTransform = Matrix3::Invert(((Node2D*)GetParent())->GetGlobalTransform()) * transform;
    } else {
        mLocalTransform = transform;
    }

    mGlobalTransform = transform;

    mDirty |= TransformDirtyFlags::LocalVectors | TransformDirtyFlags::NotifyTransform;
    mDirty &= ~TransformDirtyFlags::GlobalTransform;
}

const Matrix3& Node2D::GetGlobalTransform() const {
    if (mDirty & TransformDirtyFlags::GlobalTransform) {
        if (GetParent() && GetParent()->IsInstanceOf<Node2D>()) {
            mGlobalTransform = ((Node2D*)GetParent())->GetGlobalTransform() * GetLocalTransform();
        }
        else {
            mGlobalTransform = GetLocalTransform();
        }

        mDirty &= ~TransformDirtyFlags::GlobalTransform;
    }

    return mGlobalTransform;
}

void Node2D::OnTransformUpdate() {
}

void Node2D::OnVectorsUpdate() {
}

void Node2D::UpdateLocalVectors() const {
    mLocalPosition = Matrix3::ExtractPosition2D(mLocalTransform);
    mLocalRotation = Matrix3::ExtractEuler2D(mLocalTransform);
    // TODO: Extract scale.

    mDirty &= ~TransformDirtyFlags::LocalVectors;
}