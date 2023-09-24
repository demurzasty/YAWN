#pragma once 

#include "../Runtime/Reference.hpp"
#include "../Math/Vector2.hpp"

namespace YAWN {
    class WindowDriver : public Reference {
        YAWN_OBJECT(WindowDriver, Reference);

    public:
        virtual ~WindowDriver() = default;

        virtual void PollEvents() = 0;

        virtual bool IsOpen() const = 0;

        virtual void SwapBuffers() = 0;

        virtual Vector2 GetSize() = 0;
    };
}
