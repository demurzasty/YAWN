#pragma once 

#include "Delegate.hpp"
#include "Arena.hpp"
#include "../Core/Array.hpp"

namespace YAWN {
    template<typename... TArgs>
    class Signal {
    public:
        Signal() = default;

        Signal(const Signal<TArgs...>&) = delete;

        Signal<TArgs...>& operator=(const Signal<TArgs...>&) = delete;

        template<auto VMethod>
        void Connect() {
            Delegate<void(TArgs...)> delegate;
            delegate.Connect<VMethod>();
            mConnections.Add(delegate);
        }

        template<auto VMethod, typename T>
        void Connect(T* instance) {
            mConnections.Add(Delegate<void(TArgs...)>::Bind<VMethod>(instance));
        }

        template<typename T>
        void Disconnect(T* instance) {
            for (int i = 0; i < mConnections.GetSize(); ++i) {
                if (mConnections[i].GetInstance().Get() == instance) {
                    mConnections.RemoveAt(i);
                    return;
                }
            }
        }

        void Emit(TArgs&&... args) {
            for (Delegate<void(TArgs...)>& delegate : mConnections) {
                delegate(Utility::Forward<TArgs>(args)...);
            }
        }

    private:
        Array<Delegate<void(TArgs...)>> mConnections;
    };
}
