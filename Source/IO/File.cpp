#include <YAWN/IO/File.hpp>
#include <YAWN/Reflection/Types.hpp>

#include <stdio.h>

using namespace YAWN;

String File::ReadAllText(const Path& path) {
    FILE* file = fopen(path.ToString().ToUTF8().GetData(), "rb");
    YAWN_ASSERT(file);

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    Array<char> utf8(size + 1);
    fread(utf8.GetData(), 1, size, file);
    utf8[size] = 0;

    fclose(file);

    return String::FromUTF8(utf8.GetData());
}

Ref<Buffer> File::ReadAll(const Path& path) {
    FILE* file = fopen(path.ToString().ToUTF8().GetData(), "rb");
    YAWN_ASSERT(file);

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    Ref<Buffer> buffer = new Buffer(size);
    fread(buffer->GetData(), 1, size, file);

    fclose(file);

    return buffer;
}

void File::WriteAllText(const Path& path, const String& content) {
    File file;
    file.Open(path, FileModeFlags::Write);
    YAWN_ASSERT(file.IsOpen());

    Array<char> utf8 = content.ToUTF8();
    file.Write(utf8.GetData(), utf8.GetSize() - 1);
}

void File::Copy(const Path& input, const Path& output) {
    FILE* file = fopen(input.ToString().ToUTF8().GetData(), "rb");
    YAWN_ASSERT(file);

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    Array<char> data(size);
    fread(data.GetData(), 1, size, file);
    fclose(file);

    file = fopen(output.ToString().ToUTF8().GetData(), "wb");
    YAWN_ASSERT(file);

    fwrite(data.GetData(), 1, size, file);
    fclose(file);
}

struct FileTypeWriter : public Reference {
    File* File = nullptr;
    Ref<Reference> Object;

    void WriteTypeFields(const String& name, const Field& field);
};

File::File(File&& file) noexcept
    : mHandle(file.mHandle), mMode(file.mMode) {
    file.mHandle = nullptr;
    file.mMode = 0;
}

File& File::operator=(File&& file) noexcept {
    Close();

    mHandle = file.mHandle;
    mMode = file.mMode;

    file.mHandle = nullptr;
    file.mMode = 0;

    return *this;
}

bool File::Open(const Path& path, int mode) {
    Close();

    const char* internalMode = "";
    switch (mode) {
    case FileModeFlags::Read:
        internalMode = "rb";
        break;
    case FileModeFlags::Write:
        internalMode = "wb";
        break;
    case FileModeFlags::ReadWrite:
        internalMode = "r+b";
        break;
    case FileModeFlags::WriteRead:
        internalMode = "w+b";
        break;
    }

    mHandle = fopen(path.ToString().ToUTF8().GetData(), internalMode);
    mMode = mode;

    return mHandle != nullptr;
}

void File::Close() {
    if (mHandle) {
        fclose((FILE*)mHandle);
        mHandle = nullptr;
    }
}

bool File::IsOpen() const {
    return mHandle;
}

File::~File() {
    Close();
}

void File::Read(void* data, int size) {
    YAWN_ASSERT(IsOpen());

    fread(data, 1, size_t(size), (FILE*)mHandle);
}

int File::Read8() {
    YAWN_ASSERT(IsOpen());

    char value;
    fread(&value, 1, 1, (FILE*)mHandle);
    return value;
}

int File::Read16() {
    YAWN_ASSERT(IsOpen());

    short value;
    fread(&value, 2, 1, (FILE*)mHandle);
    return value;
}

int File::Read32() {
    YAWN_ASSERT(IsOpen());

    int value;
    fread(&value, 4, 1, (FILE*)mHandle);
    return value;
}

long long File::Read64() {
    YAWN_ASSERT(IsOpen());

    long long value;
    fread(&value, 8, 1, (FILE*)mHandle);
    return value;
}

float File::ReadFloat() {
    YAWN_ASSERT(IsOpen());

    float value;
    fread(&value, 4, 1, (FILE*)mHandle);
    return value;
}

Variant File::ReadVariant() {
    YAWN_ASSERT(IsOpen());

    VariantType type = VariantType(Read8());

    switch (type) {
        case VariantType::Boolean:
            return bool(Read8());
        case VariantType::Integer:
            return Read32();
        case VariantType::FloatingPoint:
            return ReadFloat();
        case VariantType::String: {
            Variant variant;
            int length = Read32();
            Array<wchar_t> string(length);
            for (int i = 0; i < length; ++i) {
                string[i] = Read32();
            }
            return String(string.GetData(), length);
        }
        case VariantType::Array: {
            int length = Read32();
            Array<Variant> array(length);
            for (int i = 0; i < length; ++i) {
                array[i] = ReadVariant();
            }
            return array;
        }
        case VariantType::Map: {
            int length = Read32();
            Map<String, Variant> map;
            for (int i = 0; i < length; ++i) {
                int stringLength = Read32();
                Array<wchar_t> string(stringLength);
                for (int i = 0; i < stringLength; ++i) {
                    string[i] = Read32();
                }
                map.Add(String(string.GetData(), stringLength), ReadVariant());
            }
            return map;
        }
        case VariantType::Object: {
            YAWN_ASSERT(0);
            break;
        }
    }

    return Variant();
}

void File::Write(const void* data, int size) {
    YAWN_ASSERT(IsOpen());

    fwrite(data, 1, size, (FILE*)mHandle);
}

void File::Write8(int value) {
    YAWN_ASSERT(IsOpen());

    fwrite(&value, 1, 1, (FILE*)mHandle);
}

void File::Write16(int value) {
    YAWN_ASSERT(IsOpen());

    fwrite(&value, 2, 1, (FILE*)mHandle);
}

void File::Write32(int value) {
    YAWN_ASSERT(IsOpen());

    fwrite(&value, 4, 1, (FILE*)mHandle);
}

void File::Write64(long long value) {
    YAWN_ASSERT(IsOpen());

    fwrite(&value, 8, 1, (FILE*)mHandle);
}

void File::WriteFloat(float value) {
    YAWN_ASSERT(IsOpen());

    fwrite(&value, 4, 1, (FILE*)mHandle);
}

void File::WriteVariant(const Variant& variant) {
    YAWN_ASSERT(IsOpen());

    Write8(int(variant.GetType()));

    switch (variant.GetType()) {
    case VariantType::Boolean:
        Write8(variant.AsBool() ? 1 : 0);
        break;
    case VariantType::Integer:
        Write32(variant.AsInt());
        break;
    case VariantType::FloatingPoint:
        WriteFloat(variant.AsFloat());
        break;
    case VariantType::String:
        Write32(variant.AsString().GetSize());
        for (int i = 0; i < variant.AsString().GetSize(); ++i) {
            Write32(variant.AsString()[i]);
        }
        break;
    case VariantType::Array:
        Write32(variant.AsArray().GetSize());
        for (const Variant& element : variant.AsArray()) {
            WriteVariant(element);
        }
        break;
    case VariantType::Map:
        Write32(variant.AsMap().GetSize());
        for (const KeyValue<String, Variant>& element : variant.AsMap()) {
            Write32(element.Key.GetSize());
            for (int j = 0; j < element.Key.GetSize(); ++j) {
                Write32(element.Key[j]);
            }

            WriteVariant(element.Value);
        }
        break;
    case VariantType::Object:
        if (variant.AsObject()) {
            Ref<Type> type = Types::GetType(variant.AsObject()->GetTypeId());

            Write32(type->GetName().GetSize());
            for (int i = 0; i < type->GetName().GetSize(); ++i) {
                Write32(type->GetName()[i]);
            }

            FileTypeWriter writer;
            writer.File = this;
            writer.Object = variant.AsObject();

            Delegate<void(const String&, const Field&)> delegate;
            delegate.Connect<&FileTypeWriter::WriteTypeFields>(&writer);

            type->EnumerateFields(delegate);
        } else {
            Write32(0);
        }
        break;
    }
}

void FileTypeWriter::WriteTypeFields(const String& name, const Field& field) {
    File->Write32(name.GetSize());
    for (int i = 0; i < name.GetSize(); ++i) {
        File->Write32(name[i]);
    }

    File->WriteVariant(field.Get(Object.Get()));
}
