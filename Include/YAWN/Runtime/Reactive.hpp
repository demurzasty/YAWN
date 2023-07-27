#pragma once 

#include "Reference.hpp"
#include "Signal.hpp"
#include "../Core/Array.hpp"

namespace YAWN {
    struct Connection {
        Ref<Reference> Instance = nullptr;
        const void* Method = nullptr;
    };

    class Reactive : public Reference {
        YAWN_OBJECT(Reactive, Reference);

    public:
        virtual ~Reactive() = default;

        void DisconnectAll();

        template<typename... TArgs>
        void Connect(Signal<TArgs...>& signal, const Delegate<void(TArgs...)>& delegate) {
            // GetOwner()->GetTransformUpdateSignal().Connect<&Camera::OnTransformUpdate>(this);
        }

        template<auto VMethod, typename T, typename... TArgs>
        void Connect(Signal<TArgs...>& signal, T& instance) {

        }

    private:

    };
}
