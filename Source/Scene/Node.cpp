#include <YAWN/Scene/Node3D.hpp>
#include <YAWN/Graphics/Renderer.hpp>

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

void Node::Redraw() {
    if (mNeedRedraw) {
        mVertices.Clear();
        mIndices.Clear();
        mDrawCommands.Clear();

        Draw();

        mNeedRedraw = false;
    }

    if (!mDrawCommands.IsEmpty()) {
        Renderer::LLSetVertexBufferData2D(mVertices);
        Renderer::LLSetIndexBufferData2D(mIndices);

        for (const DrawCommand& command : mDrawCommands) {
            Renderer::LLSetTexture2D(command.TextureId);

            Renderer::LLDraw2D(command.VertexOffset, command.IndexOffset, command.IndexCount);
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


void Node::DrawTexture(int textureId, const Rectangle& destination, const Rectangle& source, const Color4& color) {
    Vector2 position = destination.GetPosition();
    Vector2 size = destination.GetSize();
    Vector2 textureSize = Renderer::GetTextureSize(textureId);

    Vertex2D vertices[4] = {
        Vertex2D(position, Vector2(source.Left / textureSize.X, source.Top / textureSize.Y), color),
        Vertex2D(position + Vector2(0.0f, size.Y), Vector2(source.Left / textureSize.X, source.GetBottom() / textureSize.Y), color),
        Vertex2D(position + Vector2(size.X, size.Y), Vector2(source.GetRight() / textureSize.X, source.GetBottom() / textureSize.Y), color),
        Vertex2D(position + Vector2(size.X, 0.0f), Vector2(source.GetRight() / textureSize.X, source.Top / textureSize.Y), color),
    };

    unsigned short indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    AddDrawCommand(textureId, vertices, indices);
}

void Node::DrawText(const Ref<Font>& font, int size, const Vector2& destination, const String& text, const Color4& color) {
    Vector2 position = destination;
    for (int i = 0; i < text.GetSize(); ++i) {
        const FontGlyph& glyph = font->GetGlyph(text[i], size);

        DrawTexture(font->GetTextureId(),
            Rectangle(position.X + glyph.Offset.X, position.Y + glyph.Offset.Y + size, glyph.Rectangle.Width, glyph.Rectangle.Height),
            glyph.Rectangle,
            color);

        position.X += glyph.Advance;

        if (i + 1 < text.GetSize()) {
            position.X += font->GetKerning(text[i], text[i + 1], size);
        }
    }
}

void Node::AddDrawCommand(int textureId, const ArrayView<const Vertex2D>& vertices, const ArrayView<const unsigned short>& indices) {
    DrawCommand command;
    command.TextureId = textureId;
    command.VertexOffset = mVertices.GetSize();
    command.IndexOffset = mIndices.GetSize();
    command.IndexCount = indices.GetSize();
    
    mVertices.AddRange(vertices.GetData(), vertices.GetSize());
    mIndices.AddRange(indices.GetData(), indices.GetSize());
    mDrawCommands.Add(command);
}
