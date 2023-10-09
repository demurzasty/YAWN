#pragma once 

#include "Geometry3D.hpp"

namespace YAWN {
    class Gizmo3D : public Geometry3D {
        YAWN_OBJECT(Gizmo3D, Node3D);

    public:
        static void Register(Meta<Gizmo3D>& meta);

    public:
        Gizmo3D();

        virtual ~Gizmo3D() = default;
    };
}
