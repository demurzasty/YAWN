#pragma once 

#include "../Core/String.hpp"
#include "../Core/Array.hpp"

namespace YAWN {
    class Path {
    public:
        Path() = default;

        Path(const wchar_t* path);

        Path(const String& path);

        Path(const Path&) = default;

        Path(Path&&) noexcept = default;

        Path& operator=(const Path&) = default;

        Path& operator=(Path&&) noexcept = default;

        Path operator/(const Path& path) const;

        bool operator==(const Path& path) const;

        bool operator!=(const Path& path) const;

        Path GetRoot() const;

        String GetFilename() const;

        String GetStem() const;

        bool HasExtension() const;

        String GetExtension() const;

        String ToString() const;

    private:
        Array<String> mParts;
    };
}
