#include <YAWN/Runtime/JSON.hpp>
#include <YAWN/IO/File.hpp>
#include <YAWN/Reflection/Types.hpp>
#include <YAWN/Runtime/Console.hpp>

// TODO: Write our own parser to avoid boilerplate.

#include <json.h>
#include <string.h>

using namespace YAWN;

static void ParseJson(json_object* json, Variant& output);

static void ParseObject(json_object* json, Variant& output) {
    const char* typeName = json_object_get_string(json_object_object_get(json, "$Type"));
    Type* type = Types::GetTypeByName(String::FromUTF8(typeName));
    YAWN_ASSERT(type);

    Ref<Reference> ref = type->Construct();

    json_object_object_foreach(json, key, val) {
        if (key[0] != '$') {
            Variant value;
            ParseJson(val, value);

            const Field& field = type->GetField(String::FromUTF8(key));
            if (field.IsAssignable()) {
                field.Set(ref.Get(), value);
            }
        }
    }

    output = ref;
}

static void ParseMap(json_object* json, Variant& output) {
    output = Variant::MakeMap();

    json_object_object_foreach(json, key, val) {
        Variant value;
        ParseJson(val, value);
        output.AsMap().Add(String::FromUTF8(key), value);
    }
}

static void ParseVector2(json_object* json, Variant& output) {
    Vector2 vec = Vector2::Zero;

    vec.X = (float)json_object_get_double(json_object_object_get(json, "X"));
    vec.Y = (float)json_object_get_double(json_object_object_get(json, "Y"));
    
    output = vec;
}

static void ParseVector3(json_object* json, Variant& output) {
    Vector3 vec = Vector3::Zero;

    vec.X = (float)json_object_get_double(json_object_object_get(json, "X"));
    vec.Y = (float)json_object_get_double(json_object_object_get(json, "Y"));
    vec.Z = (float)json_object_get_double(json_object_object_get(json, "Z"));

    output = vec;
}

static void ParseVector4(json_object* json, Variant& output) {
    Vector4 vec = Vector4::Zero;

    vec.X = (float)json_object_get_double(json_object_object_get(json, "X"));
    vec.Y = (float)json_object_get_double(json_object_object_get(json, "Y"));
    vec.Z = (float)json_object_get_double(json_object_object_get(json, "Z"));
    vec.W = (float)json_object_get_double(json_object_object_get(json, "W"));

    output = vec;
}

static void ParseArray(json_object* json, Variant& output) {
    output = Variant::MakeArray();

    size_t length = json_object_array_length(json);
    for (size_t i = 0; i < length; ++i) {
        json_object* element = json_object_array_get_idx(json, i);

        Variant value;
        ParseJson(element, value);
        output.AsArray().Add(value);
    }
}

static void ParseJson(json_object* json, Variant& output) {
    if (json_object_is_type(json, json_type_object)) {
        json_object* type = json_object_object_get(json, "$Type");
        if (type) {
            const char* typeName = json_object_get_string(type);
            if (strcmp(typeName, "Vector2") == 0) {
                ParseVector2(json, output);
            } else if (strcmp(typeName, "Vector3") == 0) {
                ParseVector3(json, output);
            } else if (strcmp(typeName, "Vector4") == 0) {
                ParseVector4(json, output);
            } else {
                ParseObject(json, output);
            }
        } else {
            ParseMap(json, output);
        }
    } else if (json_object_is_type(json, json_type_string)) {
        output = String::FromUTF8(json_object_get_string(json));
    } else if (json_object_is_type(json, json_type_int)) {
        output = json_object_get_int64(json);
    } else if (json_object_is_type(json, json_type_double)) {
        output = json_object_get_double(json);
    } else if (json_object_is_type(json, json_type_boolean)) {
        output = bool(json_object_get_boolean(json));
    } else if (json_object_is_type(json, json_type_array)) {
        ParseArray(json, output);
    } else {
        output = Variant();
    }
}

Variant JSON::Parse(const String& text) {
    json_object* root = json_tokener_parse(text.ToUTF8().GetData());
    if (!root) {
        return Variant();
    }

    Variant output;
    ParseJson(root, output);

    json_object_put(root);
    return output;
}

Map<String, Variant> JSON::ParseFromFile(const String& path) {
    return Parse(File::ReadAllText(path));
}

static json_object* BuildJson(const Variant& data);

static json_object* BuildMap(const Map<String, Variant>& map) {
    json_object* object = json_object_new_object();
    
    for (const KeyValue<String, Variant>& pair : map) {
        json_object_object_add(object, pair.Key.ToUTF8().GetData(), BuildJson(pair.Value));
    }

    return object;
}

class ObjectBuilder : public Reference {
public:
    ObjectBuilder(json_object* object, Ref<Reference> ref) : mObject(object), mRef(ref) {}

    void BuildMember(const String& name, const Field& field) {
        Variant value;
        field.Get(mRef.Get(), value);
        json_object_object_add(mObject, name.ToUTF8().GetData(), BuildJson(value));
    }

private:
    json_object* mObject;
    Ref<Reference> mRef;
};

static json_object* BuildObject(const Ref<Reference>& ref) {
    json_object* object = json_object_new_object();

    Type& type = Types::GetType(ref->GetTypeId());

    Ref<ObjectBuilder> builder = new ObjectBuilder(object, ref);
    type.EnumerateFields(Delegate<void(const String&, const Field&)>::Bind<&ObjectBuilder::BuildMember>(builder.Get()));

    json_object_object_add(object, "$Type", json_object_new_string(String(ref->GetTypeName()).ToUTF8().GetData()));

    return object;
}

static json_object* BuildArray(const Array<Variant>& array) {
    json_object* object = json_object_new_array();

    for (const Variant& element : array) {
        json_object_array_add(object, BuildJson(element));
    }

    return object;
}

static json_object* BuildVector2(const Vector2& vec) {
    json_object* object = json_object_new_object();

    json_object_object_add(object, "X", json_object_new_double(vec.X));
    json_object_object_add(object, "Y", json_object_new_double(vec.Y));
    json_object_object_add(object, "$Type", json_object_new_string("Vector2"));

    return object;
}

static json_object* BuildVector3(const Vector3& vec) {
    json_object* object = json_object_new_object();

    json_object_object_add(object, "X", json_object_new_double(vec.X));
    json_object_object_add(object, "Y", json_object_new_double(vec.Y));
    json_object_object_add(object, "Z", json_object_new_double(vec.Z));
    json_object_object_add(object, "$Type", json_object_new_string("Vector3"));

    return object;
}

static json_object* BuildVector4(const Vector4& vec) {
    json_object* object = json_object_new_object();

    json_object_object_add(object, "X", json_object_new_double(vec.X));
    json_object_object_add(object, "Y", json_object_new_double(vec.Y));
    json_object_object_add(object, "Z", json_object_new_double(vec.Z));
    json_object_object_add(object, "W", json_object_new_double(vec.W));
    json_object_object_add(object, "$Type", json_object_new_string("Vector4"));

    return object;
}

static json_object* BuildJson(const Variant& data) {
    if (data.GetType() == VariantType::Map) {
        return BuildMap(data.AsMap());
    } else if (data.GetType() == VariantType::String) {
        return json_object_new_string(data.AsString().ToUTF8().GetData());
    } else if (data.GetType() == VariantType::Integer) {
        return json_object_new_int64(data.AsLongLong());
    } else if (data.GetType() == VariantType::Boolean) {
        return json_object_new_boolean(data.AsBool() ? 1 : 0);
    } else if (data.GetType() == VariantType::Array) {
        return BuildArray(data.AsArray());
    } else if (data.GetType() == VariantType::Object) {
        return BuildObject(data.AsObject());
    } else if (data.GetType() == VariantType::Vector2) {
        return BuildVector2(data.AsVector2());
    } else if (data.GetType() == VariantType::Vector3) {
        return BuildVector3(data.AsVector3());
    } else if (data.GetType() == VariantType::Vector4) {
        return BuildVector4(data.AsVector4());
    }

    return json_object_new_null();
}

String JSON::Stringify(const Variant& data) {
    json_object* root = BuildJson(data);

    String output = String::FromUTF8(json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));

    json_object_put(root);
    return output;
}
