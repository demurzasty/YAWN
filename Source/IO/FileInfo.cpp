#include <YAWN/IO/FileInfo.hpp>

using namespace YAWN;

FileInfo::FileInfo(const Path& path, long long lastWriteTime)
    : mPath(path), mLastWriteTime(lastWriteTime) {
}

FileInfo::FileInfo(Path&& path, long long lastWriteTime)
    : mPath(Utility::Forward<Path>(path)), mLastWriteTime(lastWriteTime) {
}

const Path& FileInfo::GetPath() const {
    return mPath;
}

long long FileInfo::GetLastWriteTime() const {
    return mLastWriteTime;
}
