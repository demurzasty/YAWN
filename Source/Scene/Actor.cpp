#include <YAWN/Scene/Actor.hpp>

using namespace YAWN;

void Actor::Register(Meta<Actor>& meta) {
    meta.SetBase<Reference>();
    meta.SetName(L"Actor");
    meta.SetConstructable();
    meta.AddField<&Actor::SetName, &Actor::GetName>(L"Name");
}

Actor::~Actor() {
    for (KeyValue<int, Ref<Component>>& component : mComponents) {
        component.Value->Exit();
    }
}

void Actor::AddComponent(const Ref<Component>& component) {
    YAWN_ASSERT(component);
    YAWN_ASSERT(!mComponents.Contains(component->GetTypeId()));

    mComponents.Add(component->GetTypeId(), component);

    component->mOwner = this;

    component->Enter();
}

bool Actor::HasComponent(int typeId) {
    return mComponents.Contains(typeId);
}

Ref<Component> Actor::GetComponent(int typeId) {
    YAWN_ASSERT(HasComponent(typeId));

    return mComponents[typeId];
}

void Actor::Update(float timeStep) {
    for (KeyValue<int, Ref<Component>>& component : mComponents) {
        component.Value->Update(timeStep);
    }
}

void Actor::LateUpdate(float timeStep) {
    if (mDirty & TransformDirtyFlags::NotifyTransform) {
        for (const Ref<Actor>& actor : GetChildren()) {
            actor->mDirty |= TransformDirtyFlags::All;
        }

        mTransformUpdateSignal.Emit(this);

        mDirty &= ~TransformDirtyFlags::NotifyTransform;
    }

    if (mDirty & TransformDirtyFlags::NotifyVectors) {
        mTransformUpdateSignal.Emit(this);

        mDirty &= ~TransformDirtyFlags::NotifyVectors;
    }

    for (KeyValue<int, Ref<Component>>& component : mComponents) {
        component.Value->LateUpdate(timeStep);
    }
}

void Actor::FixedUpdate(float timeStep) {
    for (KeyValue<int, Ref<Component>>& component : mComponents) {
        component.Value->FixedUpdate(timeStep);
    }
}

void Actor::SetName(const String& name) {
    mName = name;
}

const String& Actor::GetName() const {
    return mName;
}

Actor* Actor::GetParent() const {
    return mParent;
}

void Actor::AddChild(const Ref<Actor>& node) {
    YAWN_ASSERT(node);
    YAWN_ASSERT(!node->mParent);

    node->mParent = this;
    mChildren.Add(node);
}

void Actor::AddSibling(const Ref<Actor>& node) {
    YAWN_ASSERT(mParent);

    mParent->AddChild(node);
}

ArrayView<const Ref<Actor>> Actor::GetChildren() const {
    return mChildren;
}

void Actor::SetLocalPosition(const Vector3& position) {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    mLocalPosition = position;
    mDirty |= TransformDirtyFlags::LocalTransform | TransformDirtyFlags::GlobalTransform | TransformDirtyFlags::Notify;
}

const Vector3& Actor::GetLocalPosition() const {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    return mLocalPosition;
}

void Actor::SetLocalRotation(const Vector3& rotation) {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    mLocalRotation = rotation;
    mDirty |= TransformDirtyFlags::LocalTransform | TransformDirtyFlags::GlobalTransform | TransformDirtyFlags::Notify;
}

const Vector3& Actor::GetLocalRotation() const {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    return mLocalRotation;
}

void Actor::SetLocalScale(const Vector3& scale) {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    mLocalScale = scale;
    mDirty |= TransformDirtyFlags::LocalTransform | TransformDirtyFlags::GlobalTransform | TransformDirtyFlags::Notify;
}

const Vector3& Actor::GetLocalScale() const {
    if (mDirty & TransformDirtyFlags::LocalVectors) {
        UpdateLocalVectors();
    }

    return mLocalScale;
}

void Actor::SetLocalTransform(const Matrix4& transform) {
    mLocalTransform = transform;
    mDirty |= TransformDirtyFlags::LocalVectors | TransformDirtyFlags::GlobalTransform | TransformDirtyFlags::NotifyTransform;
    mDirty &= ~TransformDirtyFlags::LocalTransform;
}

const Matrix4& Actor::GetLocalTransform() const {
    if (mDirty & TransformDirtyFlags::LocalTransform) {
        mLocalTransform = Matrix4::CreateTranslation(mLocalPosition) *
            Matrix4::CreateRotation(mLocalRotation) *
            Matrix4::CreateScaling(mLocalScale);

        mDirty &= ~TransformDirtyFlags::LocalTransform;
    }

    return mLocalTransform;
}

Vector3 Actor::GetGlobalPosition() const {
    return Matrix4::ExtractPosition(GetGlobalTransform());
}

Vector3 Actor::GetGlobalRotation() const {
    return Matrix4::ExtractEuler(GetGlobalTransform());
}

void Actor::SetGlobalTransform(const Matrix4& transform, bool notify) {
    if (mParent) {
        mLocalTransform = Matrix4::Invert(mParent->GetGlobalTransform()) * transform;
    } else {
        mLocalTransform = transform;
    }

    mGlobalTransform = transform;

    mDirty |= TransformDirtyFlags::LocalVectors | TransformDirtyFlags::NotifyTransform;
    mDirty &= ~TransformDirtyFlags::GlobalTransform;
}

const Matrix4& Actor::GetGlobalTransform() const {
    if (mDirty & TransformDirtyFlags::GlobalTransform) {
        if (mParent) {
            mGlobalTransform = mParent->GetGlobalTransform() * GetLocalTransform();
        } else {
            mGlobalTransform = GetLocalTransform();
        }

        mDirty &= ~TransformDirtyFlags::GlobalTransform;
    }

    return mGlobalTransform;
}

Signal<const Ref<Actor>&>& Actor::GetTransformUpdateSignal() {
    return mTransformUpdateSignal;
}

Signal<const Ref<Actor>&>& Actor::GetVectorsUpdateSignal() {
    return mVectorsUpdateSignal;
}

void Actor::UpdateLocalVectors() const {
    mLocalPosition = Matrix4::ExtractPosition(mLocalTransform);
    mLocalRotation = Matrix4::ExtractEuler(mLocalTransform);
    // TODO: Extract scale.

    mDirty &= ~TransformDirtyFlags::LocalVectors;
}
