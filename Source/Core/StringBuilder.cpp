#include <YAWN/Core/StringBuilder.hpp>

using namespace YAWN;

void StringBuilder::Append(const String& string) {
    mString.AddRange(string.GetData(), string.GetSize());
}

void StringBuilder::AppendLine(const String& string) {
    mString.AddRange(string.GetData(), string.GetSize());
    mString.Add(U'\n');
}

String StringBuilder::ToString() const {
    return String(mString.GetData(), mString.GetSize());
}
