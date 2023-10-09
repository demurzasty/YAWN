#pragma once 

#include "../Runtime/Reference.hpp"
#include "../Reflection/Meta.hpp"
#include "../Core/ArrayView.hpp"
#include "../Math/Rectangle.hpp"
#include "../Graphics/Color.hpp"
#include "../Graphics/Font.hpp"
#include "../Graphics/Vertex.hpp"
#include "../Graphics/Topology.hpp"
#include "../Platform/Event.hpp"

namespace YAWN {
    class Viewport;

    class Node : public Reference {
        YAWN_OBJECT(Node, Reference);

    public:
        static void Register(Meta<Node>& meta);

    public:
        virtual ~Node();

        //////////////////////////
        ///////// Hooks //////////
        //////////////////////////

        virtual void Enter();

        virtual void Exit();

        virtual void Update(float timeStep);

        virtual void LateUpdate(float timeStep);

        virtual void FixedUpdate(float timeStep);

        virtual void HandleEvent(const Event& event);

        virtual void Draw();

        virtual void PostDraw();

        //////////////////////////
        //////// Drawing /////////
        //////////////////////////

        void Redraw();

        void RequestRedraw();

        //////////////////////////
        ///////// Basic //////////
        //////////////////////////

        void SetName(const String& name);

        const String& GetName() const;

        void SetVisible(bool visible);

        bool IsVisible() const;

        //////////////////////////
        /////// Hierarchy ////////
        //////////////////////////

        Node* GetParent() const;

        void AddChild(const Ref<Node>& node);

        void AddSibling(const Ref<Node>& node);

        void RemoveChild(const Ref<Node>& node);

        void RemoveAllChildren();

        ArrayView<const Ref<Node>> GetChildren() const;

        int GetChildCount() const;

        const Ref<Node>& GetChild(int index) const;

        int GetIndex() const;

        bool IsFirstChild() const;

        bool IsLastChild() const;

        //////////////////////////
        //////// Viewport ////////
        //////////////////////////

        Ref<Viewport> GetViewport() const;

        //////////////////////////
        //// Input Utilities /////
        //////////////////////////

        Vector2 GetMousePosition() const;

    protected:
        ///////////////////////////
        ////////// Events /////////
        ///////////////////////////

        virtual void OnReparent();

        ///////////////////////////
        //// Drawing Utilities ////
        ///////////////////////////

        void DrawTexture(OID textureId, const Rectangle& destination, const Rectangle& source, const Color4& color, bool flipY = false);

        void DrawLine(const Vector2& from, const Vector2& to, const Color4& color);

        void DrawFillRect(const Rectangle& destination, const Color4& color);

        void DrawRect(const Rectangle& destination, const Color4& color);

        void DrawText(const Ref<Font>& font, int size, const Vector2& destination, const String& text, const Color4& color);

        void AddDrawCommand(Topology topology, OID textureId, const ArrayView<const Vertex2D>& vertices, const ArrayView<const unsigned short>& indices);

    private:
        void SetChildren(const Array<Ref<Node>>& children);

        void OnEnter();

    private:
        friend class Scene;

        //////////////////////////
        //////// Structs /////////
        //////////////////////////

        struct DrawCommand {
            Topology Topology;
            OID TextureId;
            int VertexOffset;
            int IndexOffset;
            int IndexCount;
        };

        //////////////////////////
        ///////// Basic //////////
        //////////////////////////

        String mName;
        bool mVisible = true;

        //////////////////////////
        /////// Hierarchy ////////
        //////////////////////////

        Node* mParent = nullptr;
        Array<Ref<Node>> mChildren;

        //////////////////////////
        //////// Drawing /////////
        //////////////////////////

        Array<Vertex2D> mVertices;
        Array<unsigned short> mIndices;
        Array<DrawCommand> mDrawCommands;

        //////////////////////////
        ///////// State //////////
        //////////////////////////

        bool mEntered = false;
        mutable bool mNeedRedraw = true;
    };
}
