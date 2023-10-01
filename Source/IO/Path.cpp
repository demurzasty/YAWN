#include <YAWN/IO/Path.hpp>

using namespace YAWN;

Path::Path(const wchar_t* path)
    : Path(String(path)) {
}

Path::Path(const String& path) {
    mParts = path.Replace(U'\\', U'/').Split(U'/');
}

Path Path::operator/(const Path& path) const {
    Path newPath = *this;
    for (int i = 0; i < path.mParts.GetSize(); ++i) {
        if (path.mParts[i] == L"..") {
            if (!newPath.mParts.IsEmpty()) {
                newPath.mParts.Pop();
            }
        } else {
            newPath.mParts.Add(path.mParts[i]);
        }
    }
    return newPath;
}

bool Path::operator==(const Path& path) const {
    if (mParts.GetSize() != path.mParts.GetSize()) {
        return false;
    }

    for (int i = 0; i < mParts.GetSize(); ++i) {
        if (mParts[i] != path.mParts[i]) {
            return false;
        }
    }

    return true;
}

bool Path::operator!=(const Path& path) const {
    return !(operator==(path));
}

Path Path::GetRoot() const {
    YAWN_ASSERT(!mParts.IsEmpty());

    return mParts.GetFront();
}

String Path::GetFilename() const {
    YAWN_ASSERT(!mParts.IsEmpty());

    return mParts.GetBack();
}

String Path::GetStem() const {
    YAWN_ASSERT(!mParts.IsEmpty());

    if (mParts.GetBack() == L"." || mParts.GetBack() == L"..") {
        return mParts.GetBack();
    }

    return mParts.GetBack().Substring(0, mParts.GetBack().FindLast('.'));
}

bool Path::HasExtension() const {
    if (!mParts.IsEmpty()) {
        if (mParts.GetBack() == L"." || mParts.GetBack() == L"..") {
            return false;
        }

        return mParts.GetBack().FindLast('.') > -1;
    }

    return false;
}

String Path::GetExtension() const {
    YAWN_ASSERT(HasExtension());

    return mParts.GetBack().Substring(mParts.GetBack().FindLast('.'));
}

String Path::ToString() const {
    Array<wchar_t> string;

    for (int i = 0; i < mParts.GetSize(); ++i) {
        string.AddRange(mParts[i].GetData(), mParts[i].GetSize());

        if (i < mParts.GetSize() - 1) {
            string.Add(U'/');
        }
    }

    return String(string.GetData(), string.GetSize());
}
