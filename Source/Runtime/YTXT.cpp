#include <YAWN/Runtime/YTXT.hpp>
#include <YAWN/Reflection/Types.hpp>
#include <YAWN/Core/Number.hpp>
#include <YAWN/Core/StringBuilder.hpp>

using namespace YAWN;

static const wchar_t sSplitters[] = { '{', '}', ',', '[', ']' };
static const wchar_t sWhitespaces[] = { ' ', '\t', '\r', '\n', ':' };

static void ParseValue(Variant& output, const Array<String>& tokens, int index) {
    if (index >= tokens.GetSize()) {
        output = Variant();
        return;
    }

    const String& token = tokens[index];
    if (token.GetSize() == 0) {
        output = Variant();
        return;
    }

    if (token[0] == U'"') {
        if (token.GetSize() < 2) {
            output = Variant();
            return;
        }

        output = String(&token[1], token.GetSize() - 2);
    } else if (token == L"true") {
        output = true;
    } else if (token == L"false") {
        output = false;
    } else if (token == L"null") {
        output = Variant();
    } else if (token.Find(U'.') > -1) {
        output = Number::ToFloat(token);
    } else {
        output = Number::ToLongLong(token);
    }
}

static void ParseMap(Map<String, Variant>& map, const Array<String>& tokens, int& index) {
    while (index + 1 < tokens.GetSize()) {
        Variant variant;
        ParseValue(variant, tokens, index + 1);
        map.Add(tokens[index], variant);
        index += 2;
    }
}

Map<String, Variant> YTXT::Parse(const String& text) {
    Map<String, Variant> output;

    Array<String> tokens = text.Tokenize(sSplitters, sWhitespaces, true);
    
    int index = 0;
    ParseMap(output, tokens, index);

    return output;
}

String YTXT::Stringify(const Map<String, Variant>& data) {
    StringBuilder builder;

    for (const KeyValue<String, Variant>& element : data) {
        builder.Append(element.Key);
        builder.Append(L": ");
        builder.Append(Stringify(element.Value));
        builder.Append(L"\n");
    }

    return builder.ToString();

}

String YTXT::Stringify(const Variant& data) {
    switch (data.GetType()) {
        case VariantType::Null: return L"null";
        case VariantType::Boolean:
            return data.AsBool() ? L"true" : L"false";
        case VariantType::Integer:
            return Number::ToString(data.AsLongLong());
        case VariantType::FloatingPoint:
            return Number::ToString(data.AsFloat());
        case VariantType::String: {
            StringBuilder builder;

            builder.Append(L"\"");
            builder.Append(data.AsString());
            builder.Append(L"\"");

            return builder.ToString();
        }
    }
    return String();
}
