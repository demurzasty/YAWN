#include <YAWN/Scene/Node3D.hpp>

using namespace YAWN;

void Node::Register(Meta<Node>& meta) {
    meta.SetBase<Reactive>();
    meta.SetName(L"Node");
    meta.SetConstructable();
    meta.AddField<&Node::SetName, &Node::GetName>(L"Name");
}

Node::~Node() {
}

void Node::Update(float timeStep) {
}

void Node::LateUpdate(float timeStep) {
}

void Node::FixedUpdate(float timeStep) {
}

void Node::SetName(const String& name) {
    mName = name;
}

const String& Node::GetName() const {
    return mName;
}

Node* Node::GetParent() const {
    return mParent;
}

void Node::AddChild(const Ref<Node>& node) {
    YAWN_ASSERT(node);
    YAWN_ASSERT(!node->mParent);

    node->mParent = this;
    mChildren.Add(node);
}

void Node::AddSibling(const Ref<Node>& node) {
    YAWN_ASSERT(mParent);

    mParent->AddChild(node);
}

ArrayView<const Ref<Node>> Node::GetChildren() const {
    return mChildren;
}

void Node::OnEnter() {
}

void Node::OnExit() {
}
