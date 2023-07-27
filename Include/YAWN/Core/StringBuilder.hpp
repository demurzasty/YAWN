#pragma once 

#include "String.hpp"

namespace YAWN {
    class StringBuilder {
    public:
        void Append(const String& string);

        void AppendLine(const String& string);

        String ToString() const;

    private:
        Array<wchar_t> mString;
    };
}
