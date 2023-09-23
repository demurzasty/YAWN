#pragma once 

#include "Node2D.hpp"
#include "../Graphics/Vertex.hpp"

namespace YAWN {
    class ImGui2D : public Node2D {
        YAWN_OBJECT(ImGui2D, Node2D);

    public:
        virtual void Enter() override;

        virtual void Exit() override;

        virtual void Update(float timeStep) override;

        virtual void Draw() override;
    };
}
