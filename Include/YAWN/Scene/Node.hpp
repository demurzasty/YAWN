#pragma once 

#include "../Runtime/Reference.hpp"
#include "../Reflection/Meta.hpp"
#include "../Core/ArrayView.hpp"

namespace YAWN {
    class Node : public Reference {
        YAWN_OBJECT(Node, Reference);

    public:
        static void Register(Meta<Node>& meta);

    public:
        virtual ~Node();

        //////////////////////////
        /////// Frame Loop ///////
        //////////////////////////

        virtual void Update(float timeStep);

        virtual void LateUpdate(float timeStep);

        virtual void FixedUpdate(float timeStep);

        virtual void Draw();

        //////////////////////////
        ///////// Basic //////////
        //////////////////////////

        void SetName(const String& name);

        const String& GetName() const;

        //////////////////////////
        /////// Hierarchy ////////
        //////////////////////////

        Node* GetParent() const;

        void AddChild(const Ref<Node>& node);

        void AddSibling(const Ref<Node>& node);

        ArrayView<const Ref<Node>> GetChildren() const;

        //////////////////////////
        //////// Events //////////
        //////////////////////////

        virtual void Enter();

        virtual void Exit();

    private:
        void SetChildren(const Array<Ref<Node>>& children);

    private:
        //////////////////////////
        ///////// Basic //////////
        //////////////////////////

        String mName;

        //////////////////////////
        /////// Hierarchy ////////
        //////////////////////////

        Node* mParent = nullptr;
        Array<Ref<Node>> mChildren;
    };
}
