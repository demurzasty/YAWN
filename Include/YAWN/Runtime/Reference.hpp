#pragma once 

#include "Object.hpp"

namespace YAWN {
    class Reference : public Object {
        YAWN_OBJECT(Reference, Object);

    public:
        virtual ~Reference();

        void IncRef();

        void DecRef();

        int GetUseCount() const;

    private:
        int mCounter = 0;
    };

    template<typename TReference>
    class Ref {
        template<typename TDerived>
        friend class Ref;

    public:
        Ref() = default;

        constexpr Ref(decltype(nullptr)) : mReference(nullptr) {}

        Ref(TReference* reference)
            : mReference(reference) {
            IncRef();
        }

        Ref(const Ref<TReference>& ref)
            : mReference(ref.mReference) {
            IncRef();
        }

        template<typename TDerived>
        Ref(const Ref<TDerived>& derived)
            : mReference(derived.mReference) {
            IncRef();
        }

        Ref(Ref<TReference>&& ref) noexcept
            : mReference(ref.mReference) {
            ref.mReference = nullptr;
        }

        ~Ref() {
            DecRef();
        }

        Ref<TReference>& operator=(const Ref<TReference>& ref) {
            DecRef();
            mReference = ref.mReference;
            IncRef();
            return *this;
        }

        Ref<TReference>& operator=(Ref<TReference>&& ref) noexcept {
            DecRef();
            mReference = ref.mReference;
            ref.mReference = nullptr;
            return *this;
        }

        void Reset() {
            *this = Ref<TReference>();
        }

        bool HasReference() const {
            return mReference != nullptr;
        }

        TReference& operator*() {
            return *mReference;
        }

        TReference* operator->() const {
            return mReference;
        }

        TReference* Get() const {
            return mReference;
        }

        operator TReference* () const {
            return mReference;
        }

        bool operator==(const Ref<TReference>& ref) const {
            return mReference == ref.mReference;
        }

        bool operator!=(const Ref<TReference>& ref) const {
            return mReference != ref.mReference;
        }

    private:
        void IncRef() {
            if (mReference) {
                mReference->IncRef();
            }
        }

        void DecRef() {
            if (mReference) {
                mReference->DecRef();
            }
        }

    private:
        TReference* mReference = nullptr;
    };

    template<typename TTo, typename TFrom>
    Ref<TTo> CastTo(const Ref<TFrom>& ref) {
        if (ref && ref->IsInstanceOf<TTo>()) {
            return Ref<TTo>((TTo*)ref.Get());
        }

        return nullptr;
    }
}
