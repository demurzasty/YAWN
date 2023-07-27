#include <YAWN/Runtime/Settings.hpp>

using namespace YAWN;

Map<String, Variant> Settings::sRecords;

void Settings::SetWindowTitle(const String& title) {
    Set(L"WindowTitle", title);
}

const String& Settings::GetWindowTitle() {
    return Get(L"WindowTitle");
}

void Settings::SetWindowWidth(int width) {
    Set(L"WindowWidth", width);
}

int Settings::GetWindowWidth() {
    return Get(L"WindowWidth");
}

void Settings::SetWindowHeight(int height) {
    Set(L"WindowHeight", height);
}

int Settings::GetWindowHeight() {
    return Get(L"WindowHeight");
}

void Settings::Set(const String& name, const Variant& value) {
    sRecords.GetOrAdd(name) = value;
}

const Variant& Settings::Get(const String& name) {
    return sRecords[name];
}
