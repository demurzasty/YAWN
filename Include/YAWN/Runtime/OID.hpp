#pragma once 

namespace YAWN {
    class OID {
    public:
        constexpr OID() noexcept = default;

        constexpr OID(int index, int version) noexcept : mIndex(index), mVersion(version) {}

        constexpr OID(decltype(nullptr)) noexcept : mIndex(-1), mVersion(-1) {}

        constexpr OID(const OID&) noexcept = default;

        constexpr OID(OID&&) noexcept = default;

        constexpr OID& operator=(const OID&) noexcept = default;

        constexpr OID& operator=(OID&&) noexcept = default;

        constexpr bool operator==(decltype(nullptr)) const noexcept { return !IsValid(); }

        constexpr bool operator!=(decltype(nullptr)) const noexcept { return IsValid(); }

        constexpr operator bool() const noexcept { return IsValid(); }

        constexpr bool IsValid() const noexcept { return mIndex >= 0 && mVersion >= 0; }

        constexpr int GetIndex() const noexcept { return mIndex; }

        constexpr int GetVersion() const noexcept { return mVersion; }

        constexpr OID Bump() const noexcept { return OID(mIndex, mVersion + 1); }

    private:
        int mIndex = -1;
        int mVersion = -1;
    };
}
