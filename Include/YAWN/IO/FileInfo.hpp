#pragma once 

#include "Path.hpp"

namespace YAWN {
    class FileInfo {
    public:
        FileInfo() = default;

        FileInfo(const Path& path, long long lastWriteTime);

        FileInfo(Path&& path, long long lastWriteTime);

        const Path& GetPath() const;

        long long GetLastWriteTime() const;

    private:
        Path mPath;
        long long mLastWriteTime = 0;
    };
}
