#include <YAWN/Scene/Node.hpp>
#include <YAWN/Graphics/Renderer.hpp>
#include <YAWN/Scene/Viewport.hpp>
#include <YAWN/Scene/UI/ViewportContainer.hpp>
#include <YAWN/Platform/Input.hpp>
#include <YAWN/Runtime/Console.hpp>

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
        if (child->mEntered) {
            child->Exit();

            child->mEntered = false;
        }
    }
}

void Node::Enter() {
    if (GetName().IsEmpty()) {
        SetName(GetTypeName());
    }
}

void Node::Exit() {
}

void Node::Update(float timeStep) {
}

void Node::LateUpdate(float timeStep) {
}

void Node::FixedUpdate(float timeStep) {
}

void Node::HandleEvent(const Event& event) {
}

void Node::Draw() {
}

void Node::PostDraw() {
}

void Node::Redraw() {
    if (mNeedRedraw) {
        mVertices.Clear();
        mIndices.Clear();
        mDrawCommands.Clear();

        Draw();

        PostDraw();

        for (const Ref<Node>& node : GetChildren()) {
            node->RequestRedraw();
        }

        mNeedRedraw = false;
    }

    if (!mDrawCommands.IsEmpty()) {
        Renderer::LLSetVertexBufferData2D(mVertices);
        Renderer::LLSetIndexBufferData2D(mIndices);

        for (const DrawCommand& command : mDrawCommands) {
            Renderer::LLSetTexture2D(command.TextureId);

            Renderer::LLDraw2D(command.Topology, command.VertexOffset, command.IndexOffset, command.IndexCount);
        }
    }
}

void Node::RequestRedraw() {
    mNeedRedraw = true;
}

void Node::SetName(const String& name) {
    mName = name;
}

const String& Node::GetName() const {
    return mName;
}

void Node::SetVisible(bool visible) {
    mVisible = visible;

    RequestRedraw();
}

bool Node::IsVisible() const {
    return mVisible;
}

Node* Node::GetParent() const {
    return mParent;
}

void Node::AddChild(const Ref<Node>& node) {
    YAWN_ASSERT(node);
    YAWN_ASSERT(!node->mParent);

    node->mParent = this;
    mChildren.Add(node);

    node->OnReparent();

    if (mEntered) {
        node->OnEnter();
    }

    RequestRedraw();
}

void Node::AddSibling(const Ref<Node>& node) {
    YAWN_ASSERT(mParent);

    mParent->AddChild(node);
}

void Node::RemoveChild(const Ref<Node>& node) {
    YAWN_ASSERT(node->mParent == this);

    node->Exit();

    node->mParent = nullptr;
    mChildren.Remove(node);

    RequestRedraw();
}

void Node::RemoveAllChildren() {
    mChildren.Clear();

    RequestRedraw();
}

int Node::GetChildCount() const {
    return mChildren.GetSize();
}

const Ref<Node>& Node::GetChild(int index) const {
    YAWN_ASSERT(index >= 0 && index < GetChildCount());

    return mChildren[index];
}

ArrayView<const Ref<Node>> Node::GetChildren() const {
    return mChildren;
}

int Node::GetIndex() const {
    // TODO: Should be cached.
    if (mParent) {
        for (int i = 0; i < mParent->GetChildCount(); ++i) {
            if (mParent->GetChild(i).Get() == this) {
                return i;
            }
        }
    }

    return -1;
}

bool Node::IsFirstChild() const {
    return GetIndex() == 0;
}

bool Node::IsLastChild() const {
    return mParent && GetIndex() == mParent->GetChildCount() - 1;
}

Ref<Viewport> Node::GetViewport() const {
    // TODO: Should be cached.

    if (mParent) {
        Viewport* viewport = CastTo<Viewport>(mParent);
        if (viewport) {
            return viewport;
        }

        return mParent->GetViewport();
    }

    return nullptr;
}

Vector2 Node::GetMousePosition() const {
    const Vector2& globalMousePosition = Input::GetMousePosition();

    Ref<Viewport> viewport = GetViewport();
    if (viewport) {
        Ref<ViewportContainer> container = CastTo<ViewportContainer>(viewport->GetParent());
        if (container) {
            return globalMousePosition - container->GetGlobalPosition();
        }
    }

    return globalMousePosition;
}

void Node::SetChildren(const Array<Ref<Node>>& children) {
    mChildren.Clear();

    for (const Ref<Node>& child : children) {
        AddChild(child);
    }
}

void Node::OnEnter() {
    if (!mEntered) {
        Enter();

        mEntered = true;

        for (const Ref<Node>& child : mChildren) {
            child->OnEnter();
        }
    }
}

void Node::OnReparent() {
}

void Node::DrawTexture(int textureId, const Rectangle& destination, const Rectangle& source, const Color4& color, bool flipY) {
    if (color.A == 0) {
        return;
    }

    const Vector2& position = destination.Position;
    const Vector2& size = destination.Size;

    Vector2 textureSize = Renderer::GetTextureSize(textureId);

    Vertex2D vertices[4] = {
        Vertex2D(position, Vector2(source.Position.X / textureSize.X, source.Position.Y / textureSize.Y), color),
        Vertex2D(position + Vector2(0.0f, size.Y), Vector2(source.Position.X / textureSize.X, source.GetEnd().Y / textureSize.Y), color),
        Vertex2D(position + Vector2(size.X, size.Y), Vector2(source.GetEnd().X / textureSize.X, source.GetEnd().Y / textureSize.Y), color),
        Vertex2D(position + Vector2(size.X, 0.0f), Vector2(source.GetEnd().X / textureSize.X, source.Position.Y / textureSize.Y), color),
    };


    vertices[0].Position += Vector2(0.25f);
    vertices[1].Position += Vector2(0.25f);
    vertices[2].Position += Vector2(0.25f);
    vertices[3].Position += Vector2(0.25f);


    if (flipY) {
        vertices[0].UV.Y = 1.0f - vertices[0].UV.Y;
        vertices[1].UV.Y = 1.0f - vertices[1].UV.Y;
        vertices[2].UV.Y = 1.0f - vertices[2].UV.Y;
        vertices[3].UV.Y = 1.0f - vertices[3].UV.Y;
    }

    unsigned short indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    AddDrawCommand(Topology::Triangles, textureId, vertices, indices);
}

void Node::DrawLine(const Vector2& from, const Vector2& to, const Color4& color) {
    Vertex2D vertices[2] = {
        Vertex2D(from, Vector2::Zero, color),
        Vertex2D(to, Vector2::One, color)
    };

    unsigned short indices[2] = {
        0, 1
    };

    AddDrawCommand(Topology::Lines, Renderer::GetWhiteTexture(), vertices, indices);
}

void Node::DrawFillRect(const Rectangle& destination, const Color4& color) {
    DrawTexture(Renderer::GetWhiteTexture(), destination, Rectangle(0.0f, 0.0f, 1.0f, 1.0f), color);
}

void Node::DrawRect(const Rectangle& destination, const Color4& color) {
    const Vector2 position = Vector2::Round(destination.Position);
    const Vector2 size = Vector2::Floor(destination.Size);

    Vertex2D vertices[4] = {
        Vertex2D(position + Vector2(0.25f, 0.25f), Vector2(0.0f, 0.0f), color),
        Vertex2D(position + Vector2(0.25f, size.Y - 0.25f), Vector2(0.0f, 1.0f), color),
        Vertex2D(position + Vector2(size.X - 0.25f, size.Y - 0.25f), Vector2(1.0f, 1.0f), color),
        Vertex2D(position + Vector2(size.X - 0.25f, 0.25f), Vector2(1.0f, 0.0f), color),
    };

    unsigned short indices[8] = {
        0, 1, 1, 2,
        2, 3, 3, 0
    };

    AddDrawCommand(Topology::Lines, Renderer::GetWhiteTexture(), vertices, indices);
}

void Node::DrawText(const Ref<Font>& font, int size, const Vector2& destination, const String& text, const Color4& color) {
    if (color.A == 0) {
        return;
    }

    Vector2 position = Vector2::Floor(destination);
    for (int i = 0; i < text.GetSize(); ++i) {
        const FontGlyph& glyph = font->GetGlyph(text[i], size);

        DrawTexture(font->GetTextureId(),
            Rectangle(position.X + glyph.Offset.X, position.Y + glyph.Offset.Y + size, glyph.Rectangle.Size.X, glyph.Rectangle.Size.Y),
            glyph.Rectangle,
            color);

        position.X += glyph.Advance;

        if (i + 1 < text.GetSize()) {
            position.X += font->GetKerning(text[i], text[i + 1], size);
        }
    }

    font->Validate();
}

void Node::AddDrawCommand(Topology topology, int textureId, const ArrayView<const Vertex2D>& vertices, const ArrayView<const unsigned short>& indices) {
    DrawCommand command;
    command.Topology = topology;
    command.TextureId = textureId;
    command.VertexOffset = mVertices.GetSize();
    command.IndexOffset = mIndices.GetSize();
    command.IndexCount = indices.GetSize();
    
    mVertices.AddRange(vertices.GetData(), vertices.GetSize());
    mIndices.AddRange(indices.GetData(), indices.GetSize());
    mDrawCommands.Add(command);
}
