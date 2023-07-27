#include <YAWN/IO/File.hpp>

#include <Windows.h>

using namespace YAWN;

bool File::Exists(const Path& path) {
    DWORD dwAttrib = GetFileAttributesW(path.ToString().GetData());

    return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}
