#pragma once 

namespace YAWN {
    class OID {
    public:
        constexpr OID() noexcept = default;

        constexpr OID(int index, int version) noexcept : mData((index & 0xFFFFF) | ((version & 0xFFF) << 20)) {}

        constexpr OID(const OID&) noexcept = default;

        constexpr OID(OID&&) noexcept = default;

        constexpr OID& operator=(const OID&) noexcept = default;

        constexpr OID& operator=(OID&&) noexcept = default;

        constexpr bool operator==(const OID& oid) const noexcept { return oid.mData == mData; }

        constexpr bool operator!=(const OID& oid) const noexcept { return oid.mData != mData; }

        constexpr bool operator>(const OID& oid) const noexcept { return mData > oid.mData; }

        constexpr bool operator<(const OID& oid) const noexcept { return mData < oid.mData; }

        constexpr explicit operator bool() const noexcept { return IsValid(); }

        constexpr int operator*() const noexcept { return GetIndex(); }

        constexpr bool IsValid() const noexcept { return mData != -1; }

        constexpr int GetIndex() const noexcept { return mData & 0xFFFFF; }

        constexpr int GetVersion() const noexcept { return (mData >> 20) & 0xFFF; }

        constexpr OID Bump() const noexcept { return OID(GetIndex(), GetVersion() + 1); }

    private:
        int mData = -1;
    };
}
