#pragma once 

#include "../Core/Utility.hpp"
#include "../Core/Assert.hpp"
#include "Reference.hpp"

namespace YAWN {
    template<typename>
    class Delegate;

    template<typename TRet, typename... TArgs>
    class Delegate<TRet(TArgs...)> {
    public:
        typedef TRet(*FunctionType)(void*, TArgs...);

    public:
        template<auto VMethod, typename T>
        static Delegate<TRet(TArgs...)> Bind(T* instance) {
            Delegate<TRet(TArgs...)> delegate;
            delegate.Connect<VMethod>(instance);
            return delegate;
        }

        template<auto VMethod>
        static Delegate<TRet(TArgs...)> Bind() {
            Delegate<TRet(TArgs...)> delegate;
            delegate.Connect<VMethod>();
            return delegate;
        }

        operator bool() const {
            return mFunction;
        }

        TRet operator()(TArgs&&... args) const {
            YAWN_ASSERT(mFunction);
            return mFunction(mInstance.Get(), Utility::Forward<TArgs>(args)...);
        }

        template<auto VMethod, typename T>
        void Connect(T* instance) {
            mInstance = instance;
            mFunction = [](void* inst, TArgs... args) {
                return (((T*)inst)->*VMethod)(Utility::Forward<TArgs>(args)...);
            };
        }

        template<auto VMethod>
        void Connect() {
            mInstance = nullptr;
            mFunction = [](void* inst, TArgs... args) {
                return VMethod(Utility::Forward<TArgs>(args)...);
            };
        }

        const Ref<Reference>& GetInstance() const {
            return mInstance;
        }

        FunctionType GetFunction() const {
            return mInstance;
        }

    private:
        Ref<Reference> mInstance = nullptr;
        FunctionType mFunction = nullptr;
    };
}
