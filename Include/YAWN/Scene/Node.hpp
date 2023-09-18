#pragma once 

#include "../Runtime/Reactive.hpp"
#include "../Reflection/Meta.hpp"
#include "../Core/ArrayView.hpp"
#include "../Math/Matrix4.hpp"
#include "../Runtime/Signal.hpp"

namespace YAWN {
    class Node : public Reactive {
        YAWN_OBJECT(Node, Reactive);

    public:
        static void Register(Meta<Node>& meta);

    public:
        virtual ~Node();

        //////////////////////////
        /////// Frame Loop ///////
        //////////////////////////

        void Update(float timeStep);

        void LateUpdate(float timeStep);

        void FixedUpdate(float timeStep);

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

        virtual void OnEnter();

        virtual void OnExit();

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
