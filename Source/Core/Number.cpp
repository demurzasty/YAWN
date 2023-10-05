#include <YAWN/Core/Number.hpp>

#include <stdio.h>
#include <stdlib.h>

using namespace YAWN;

int Number::ToInteger(const String& string) {
#ifdef _MSC_VER
    return _wtoi(string.GetData());
#else
    return atoi(string.ToUTF8().GetData());
#endif
}

long long Number::ToLongLong(const String& string) {
#ifdef _MSC_VER
    return _wtoll(string.GetData());
#else
    return atoll(string.ToUTF8().GetData());
#endif
}

float Number::ToFloat(const String& string) {
    return float(atof(string.ToUTF8().GetData()));
}

String Number::ToString(int value) {
    return String::Format(L"%f", value);
}

String Number::ToString(long long value) {
    return String::Format(L"%lld", value);
}

String Number::ToString(float value) {
    return TrimPaddingZeros(String::Format(L"%.3f", value));
}

String Number::ToString(double value) {
    return TrimPaddingZeros(String::Format(L"%.3lf", value));
}

String Number::TrimPaddingZeros(const String& string) {
    int subindex = -1;
    for (int i = string.GetSize() - 1; i >= 0; --i) {
        if (string[i] == L'.') {
            break;
        }

        if (string[i] == L'0') {
            subindex = i;
        }
    }

    if (subindex > -1) {
        return string.Substring(0, subindex + 1);
    }

    return string;
}
