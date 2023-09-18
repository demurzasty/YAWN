#pragma once 

#include "Variant.hpp"

namespace YAWN {
    class JSON {
    public:
        static Variant Parse(const String& text);

        static Map<String, Variant> ParseFromFile(const String& path);

        static String Stringify(const Variant& data);
    };
}
