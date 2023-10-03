#include <YAWN/Scene/Node3D.hpp>

using namespace YAWN;

void Node3D::Register(Meta<Node3D>& meta) {
    meta.SetConstructable();
    meta.AddField<&Node3D::SetLocalPosition, &Node3D::GetLocalPosition>(L"Position");
    meta.AddField<&Node3D::SetLocalRotation, &Node3D::GetLocalRotation>(L"Rotation");
    meta.AddField<&Node3D::SetLocalScale, &Node3D::GetLocalScale>(L"Scale");
}

Node3D::~Node3D() {
}

void Node3D::Update(float timeStep) {
}

void Node3D::LateUpdate(float timeStep) {
    if (mDirty & TransformDirtyFlags::NotifyTransform) {
        for (const Ref<Node>& node : GetChildren()) {
            if (node->IsInstanceOf<Node3D>()) {
                CastTo<Node3D>(node)->mDirty |= TransformDirtyFlags::All;
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

void Node3D::FixedUpdate(float timeStep) {
}

void Node3D::SetLocalPosition(const Vector3& position) {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    mLocalPosition = position;
    mDirty |= TransformDirtyFlags::LocalTransform | TransformDirtyFlags::GlobalTransform | TransformDirtyFlags::Notify;
}

const Vector3& Node3D::GetLocalPosition() const {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    return mLocalPosition;
}

void Node3D::SetLocalRotation(const Vector3& rotation) {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    mLocalRotation = rotation;
    mDirty |= TransformDirtyFlags::LocalTransform | TransformDirtyFlags::GlobalTransform | TransformDirtyFlags::Notify;
}

const Vector3& Node3D::GetLocalRotation() const {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    return mLocalRotation;
}

void Node3D::SetLocalScale(const Vector3& scale) {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    mLocalScale = scale;
    mDirty |= TransformDirtyFlags::LocalTransform | TransformDirtyFlags::GlobalTransform | TransformDirtyFlags::Notify;
}

const Vector3& Node3D::GetLocalScale() const {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    return mLocalScale;
}

void Node3D::SetLocalTransform(const Matrix4& transform) {
    mLocalTransform = transform;
    mDirty |= TransformDirtyFlags::LocalVectors | TransformDirtyFlags::GlobalTransform | TransformDirtyFlags::NotifyTransform;
    mDirty &= ~TransformDirtyFlags::LocalTransform;
}

const Matrix4& Node3D::GetLocalTransform() const {
    if (mDirty & TransformDirtyFlags::LocalTransform) {
        mLocalTransform = Matrix4::CreateTranslation(mLocalPosition) *
            Matrix4::CreateRotation(mLocalRotation) *
            Matrix4::CreateScaling(mLocalScale);

        mDirty &= ~TransformDirtyFlags::LocalTransform;
    }

    return mLocalTransform;
}

Vector3 Node3D::GetGlobalPosition() const {
    return Matrix4::ExtractPosition(GetGlobalTransform());
}

Vector3 Node3D::GetGlobalRotation() const {
    return Matrix4::ExtractEuler(GetGlobalTransform());
}

void Node3D::SetGlobalTransform(const Matrix4& transform, bool notify) {
    if (GetParent() && GetParent()->IsInstanceOf<Node3D>()) {
        mLocalTransform = Matrix4::Invert(((Node3D*)GetParent())->GetGlobalTransform()) * transform;
    } else {
        mLocalTransform = transform;
    }

    mGlobalTransform = transform;

    mDirty |= TransformDirtyFlags::LocalVectors | TransformDirtyFlags::NotifyTransform;
    mDirty &= ~TransformDirtyFlags::GlobalTransform;
}

const Matrix4& Node3D::GetGlobalTransform() const {
    if (mDirty & TransformDirtyFlags::GlobalTransform) {
        if (GetParent() && GetParent()->IsInstanceOf<Node3D>()) {
            mGlobalTransform = ((Node3D*)GetParent())->GetGlobalTransform() * GetLocalTransform();
        } else {
            mGlobalTransform = GetLocalTransform();
        }

        mDirty &= ~TransformDirtyFlags::GlobalTransform;
    }

    return mGlobalTransform;
}

void Node3D::OnTransformUpdate() {
}

void Node3D::OnVectorsUpdate() {
}

void Node3D::UpdateLocalVectors() const {
    mLocalPosition = Matrix4::ExtractPosition(mLocalTransform);
    mLocalRotation = Matrix4::ExtractEuler(mLocalTransform);
    // TODO: Extract scale.

    mDirty &= ~TransformDirtyFlags::LocalVectors;
}