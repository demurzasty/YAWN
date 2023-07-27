#include <YAWN/IO/Directory.hpp>

#include <Windows.h>

#ifdef SetCurrentDirectory
#undef SetCurrentDirectory
#endif

#include <wchar.h>

using namespace YAWN;

bool Directory::Exists(const Path& path) {
    DWORD dwAttrib = GetFileAttributesW(path.ToString().GetData());

    return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void Directory::Create(const Path& path) {
    if (!Exists(path)) {
        CreateDirectoryW(path.ToString().GetData(), nullptr);
    }
}

void Directory::EnumerateFiles(const Path& path, const Delegate<void(const FileInfo&)>& delegate) {
    YAWN_ASSERT(delegate);

    Path fullPath = path / L"/*";

    WIN32_FIND_DATAW findData;
    HANDLE hFind = FindFirstFileW(fullPath.ToString().GetData(), &findData);
    if (hFind != INVALID_HANDLE_VALUE) {
        while (FindNextFileW(hFind, &findData) != 0) {
            if ((findData.dwFileAttributes != INVALID_FILE_ATTRIBUTES && (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))) {
                if (wcscmp(findData.cFileName, L".") != 0 && wcscmp(findData.cFileName, L"..") != 0) {
                    EnumerateFiles(path / findData.cFileName, delegate);
                }
            } else if ((findData.dwFileAttributes != INVALID_FILE_ATTRIBUTES && !(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))) {
                ULARGE_INTEGER time;
                time.LowPart = findData.ftLastWriteTime.dwLowDateTime;
                time.HighPart = findData.ftLastWriteTime.dwHighDateTime;

                delegate(FileInfo(path / findData.cFileName, time.QuadPart));
            }
        }

        FindClose(hFind);
    }
}

void Directory::SetCurrentDirectory(const Path& path) {
    SetCurrentDirectoryW(path.ToString().GetData());
}
