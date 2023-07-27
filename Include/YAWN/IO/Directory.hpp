#pragma once 

#include "FileInfo.hpp"
#include "../Runtime/Delegate.hpp"

namespace YAWN {
    class Directory {
    public:
        static bool Exists(const Path& path);

        static void Create(const Path& path);

        static void EnumerateFiles(const Path& path, const Delegate<void(const FileInfo&)>& delegate);

        static void SetCurrentDirectory(const Path& path);
    };
}
