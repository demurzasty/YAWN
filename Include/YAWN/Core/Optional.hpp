#pragma once 

#include "Memory.hpp"
#include "Assert.hpp"

namespace YAWN {
    template<typename T>
    class Optional {
    public:
        Optional() = default;

        Optional(const T& value) : mHasValue(true) {
            Memory::Construct((T*)mData, value);
        }

        Optional(T&& value) : mHasValue(true) {
            Memory::Construct((T*)mData, Utility::Forward<T>(value));
        }

        Optional(const Optional<T>& optional) : mHasValue(optional.mHasValue) {
            if (mHasValue) {
                Memory::Construct((T*)mData, optional.GetValue());
            }
        }

        Optional(Optional<T>&& optional) noexcept : mHasValue(optional.mHasValue) {
            if (mHasValue) {
                Memory::Construct((T*)mData, Utility::Move(*(T*)optional.mData));
            }

            optional.mHasValue = false;
        }

        ~Optional() {
            if (mHasValue) {
                Memory::Destroy((T*)mData);
            }
        }

        Optional<T>& operator=(const Optional<T>& optional) {
            if (mHasValue) {
                Memory::Destroy((T*)mData);
            }

            mHasValue = optional.mHasValue;

            if (mHasValue) {
                Memory::Construct((T*)mData, optional.GetValue());
            }

            return *this;
        }

        Optional<T>& operator=(Optional<T>&& optional) noexcept {
            if (mHasValue) {
                Memory::Destroy((T*)mData);
            }

            mHasValue = optional.mHasValue;

            if (mHasValue) {
                Memory::Construct((T*)mData, Utility::Move(*(T*)optional.mData));
            }

            optional.mHasValue = false;
            return *this;
        }

        Optional<T>& operator=(const T& value) {
            if (mHasValue) {
                Memory::Destroy((T*)mData);
            }

            mHasValue = true;
            Memory::Construct((T*)mData, value);

            return *this;
        }

        const T& GetValue() const {
            YAWN_ASSERT(mHasValue);

            return *(const T*)mData;
        }

        T& GetValue() {
            YAWN_ASSERT(mHasValue);

            return *(T*)mData;
        }

        bool HasValue() const {
            return mHasValue;
        }

    private:
        unsigned char mData[sizeof(T)];
        bool mHasValue = false;
    };
}
