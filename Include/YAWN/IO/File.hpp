#pragma once 

#include "Path.hpp"
#include "../Core/Guid.hpp"
#include "../Runtime/Reference.hpp"
#include "../Runtime/Variant.hpp"
#include "../Reflection/Type.hpp"
#include "../Runtime/Buffer.hpp"

namespace YAWN {
    struct FileModeFlags {
        static constexpr int Read = 1;
        static constexpr int Write = 2;
        static constexpr int ReadWrite = Read | Write;
        static constexpr int WriteRead = ReadWrite | 4;
    };

    class File : public Reference {
        YAWN_OBJECT(File, Reference);

    public:
        static bool Exists(const Path& path);

        static String ReadAllText(const Path& path);

        static Ref<Buffer> ReadAll(const Path& path);

        static void WriteAllText(const Path& path, const String& content);

        static void Copy(const Path& input, const Path& output);

        File() = default;

        File(const File&) = delete;

        File(File&& file) noexcept;

        File& operator=(const File&) = delete;

        File& operator=(File&& file) noexcept;

        ~File();

        bool Open(const Path& path, int mode);
        
        void Close();

        bool IsOpen() const;

        void Read(void* data, int size);

        int Read8();

        int Read16();

        int Read32();

        long long Read64();

        float ReadFloat();

        Variant ReadVariant();

        void Write(const void* data, int size);

        void Write8(int value);

        void Write16(int value);

        void Write32(int value);

        void Write64(long long value);

        void WriteColor4(const Color4& value);

        void WriteGuid(const Guid& value);

        void WriteFloat(float value);

        void WriteVariant(const Variant& variant);

    private:
        void* mHandle = nullptr;
        int mMode = 0;
    };
}
