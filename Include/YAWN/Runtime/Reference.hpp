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

        Ref(TReference* reference)
            : _reference(reference) {
            IncRef();
        }

        Ref(const Ref<TReference>& ref)
            : _reference(ref._reference) {
            IncRef();
        }

        template<typename TDerived>
        Ref(const Ref<TDerived>& derived)
            : _reference(derived._reference) {
            IncRef();
        }

        Ref(Ref<TReference>&& ref) noexcept
            : _reference(ref._reference) {
            ref._reference = nullptr;
        }

        ~Ref() {
            DecRef();
        }

        Ref<TReference>& operator=(const Ref<TReference>& ref) {
            DecRef();
            _reference = ref._reference;
            IncRef();
            return *this;
        }

        Ref<TReference>& operator=(Ref<TReference>&& ref) noexcept {
            DecRef();
            _reference = ref._reference;
            ref._reference = nullptr;
            return *this;
        }

        void Reset() {
            *this = Ref<TReference>();
        }

        bool HasReference() const {
            return _reference != nullptr;
        }

        TReference& operator*() {
            return *_reference;
        }

        TReference* operator->() const {
            return _reference;
        }

        TReference* Get() const {
            return _reference;
        }

        operator TReference* () const {
            return _reference;
        }

        bool operator==(const Ref<TReference>& ref) const {
            return _reference == ref._reference;
        }

        bool operator!=(const Ref<TReference>& ref) const {
            return _reference != ref._reference;
        }

    private:
        void IncRef() {
            if (_reference) {
                _reference->IncRef();
            }
        }

        void DecRef() {
            if (_reference) {
                _reference->DecRef();
            }
        }

    private:
        TReference* _reference = nullptr;
    };

    template<typename TTo, typename TFrom>
    Ref<TTo> CastTo(const Ref<TFrom>& ref) {
        if (ref && ref->IsInstanceOf<TTo>()) {
            return Ref<TTo>((TTo*)ref.Get());
        }

        return nullptr;
    }
}
