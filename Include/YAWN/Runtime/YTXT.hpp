#pragma once 

#include "Variant.hpp"

namespace YAWN {
    class YTXT {
    public:
        static Map<String, Variant> Parse(const String& text);

        static String Stringify(const Map<String, Variant>& data);

    private:
        static String Stringify(const Variant& data);
    };
}
