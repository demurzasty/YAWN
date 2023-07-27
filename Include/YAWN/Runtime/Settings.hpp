#pragma once 

#include "../Runtime/Variant.hpp"

namespace YAWN {
    class Settings {
    public:
        static void SetWindowTitle(const String& title);

        static const String& GetWindowTitle();

        static void SetWindowWidth(int width);

        static int GetWindowWidth();

        static void SetWindowHeight(int height);

        static int GetWindowHeight();

        static void Set(const String& name, const Variant& value);

        static const Variant& Get(const String& name);

    public:
        static Map<String, Variant> sRecords;
    };
}
