#include <YAWN/Core/Number.hpp>

#include <stdio.h>
#include <stdlib.h>

using namespace YAWN;

thread_local char buffer[128];

int Number::ToInteger(const String& string) {
    return atoi(string.ToUTF8().GetData());
}

long long Number::ToLongLong(const String& string) {
    return atoll(string.ToUTF8().GetData());
}

float Number::ToFloat(const String& string) {
    return float(atof(string.ToUTF8().GetData()));
}

String Number::ToString(int value) {
    sprintf(buffer, "%d", value);
    return String::FromUTF8(buffer);
}

String Number::ToString(long long value) {
    sprintf(buffer, "%lld", value);
    return String::FromUTF8(buffer);
}

String Number::ToString(float value) {
    sprintf(buffer, "%f", value);
    return String::FromUTF8(buffer);
}
