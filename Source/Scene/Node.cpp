#include <YAWN/Scene/Node3D.hpp>

using namespace YAWN;

void Node::Register(Meta<Node>& meta) {
    meta.SetBase<Reference>();
    meta.SetName(L"Node");
    meta.SetConstructable();
    meta.AddField<&Node::SetName, &Node::GetName>(L"Name");
    meta.AddField<&Node::SetChildren, &Node::GetChildren>(L"Children");
}

Node::~Node() {
    for (const Ref<Node>& child : mChildren) {
        child->Exit();
    }
}

void Node::Update(float timeStep) {
}

void Node::LateUpdate(float timeStep) {
}

void Node::FixedUpdate(float timeStep) {
}

void Node::Draw() {
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

    node->Enter();
}

void Node::AddSibling(const Ref<Node>& node) {
    YAWN_ASSERT(mParent);

    mParent->AddChild(node);
}

ArrayView<const Ref<Node>> Node::GetChildren() const {
    return mChildren;
}

void Node::Enter() {
}

void Node::Exit() {
}

void Node::SetChildren(const Array<Ref<Node>>& children) {
    mChildren.Clear();

    for (const Ref<Node>& child : children) {
        AddChild(child);
    }
}
