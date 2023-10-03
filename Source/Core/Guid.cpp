#include <YAWN/Core/Guid.hpp>
#include <YAWN/Core/Random.hpp>

using namespace YAWN;

inline char HexToByte(wchar_t ch) {
    if (ch >= '0' && ch <= '9') {
        return char(ch - '0');
    }

    if (ch >= 'a' && ch <= 'f') {
        return char(10 + ch - 'a');
    }

    if (ch >= 'A' && ch <= 'F') {
        return char(10 + ch - 'A');
    }

    return 0;
}

inline bool IsHex(wchar_t ch) {
    return (ch >= '0' && ch <= '9') ||
        (ch >= 'a' && ch <= 'f') ||
        (ch >= 'A' && ch <= 'F');
}

inline int StringToInt(const wchar_t* string, int digitCount) {
    int result = 0;
    for (int i = 0; i < digitCount; ++i) {
        if (IsHex(string[i])) {
            result |= HexToByte(string[i]) << (i * 4);
        }
    }
    return result;
}

inline wchar_t HalfByteToHex(wchar_t byte) {
    return (byte < 10) ? ('0' + byte) : ('a' + (byte - 10));
}

inline void ByteToString(char byte, wchar_t* string) {
    string[0] = HalfByteToHex(byte & 0xF);
    string[1] = HalfByteToHex((byte >> 4) & 0xF);
}

Guid Guid::Generate(Random& random) {
    int data[4] = {
        random.Next(),
        random.Next(),
        random.Next(),
        random.Next()
    };
    return Guid(data);
}

Guid::Guid()
    : mData() {
}

Guid::Guid(int data[4]) {
    for (int i = 0; i < 4; ++i) {
        mData[i] = data[i];
    }
}

Guid::Guid(const String& data)
    : mData() {
    if (data.GetSize() == 36) {
        mData[0] = StringToInt(data.GetData(), 8);
        mData[1] = StringToInt(data.GetData() + 9, 4) | (StringToInt(data.GetData() + 14, 4) << 16);
        mData[2] = StringToInt(data.GetData() + 19, 4) | (StringToInt(data.GetData() + 24, 4) << 16);
        mData[3] = StringToInt(data.GetData() + 28, 8);
    }
}

bool Guid::operator==(const Guid& guid) const {
    return Memory::Compare(mData, guid.mData, sizeof(mData)) == 0;
}

bool Guid::operator!=(const Guid& guid) const {
    return Memory::Compare(mData, guid.mData, sizeof(mData)) != 0;
}

bool Guid::operator<(const Guid& guid) const {
    return Memory::Compare(mData, guid.mData, sizeof(mData)) < 0;
}

bool Guid::operator>(const Guid& guid) const {
    return Memory::Compare(mData, guid.mData, sizeof(mData)) > 0;
}

bool Guid::IsEmpty() const {
    static Guid empty;

    return *this == empty;
}

String Guid::ToString() const {
    wchar_t string[37];
    ByteToString(mBytes[0], &string[0]);
    ByteToString(mBytes[1], &string[2]);
    ByteToString(mBytes[2], &string[4]);
    ByteToString(mBytes[3], &string[6]);
    string[8] = '-';
    ByteToString(mBytes[4], &string[9]);
    ByteToString(mBytes[5], &string[11]);
    string[13] = '-';
    ByteToString(mBytes[6], &string[14]);
    ByteToString(mBytes[7], &string[16]);
    string[18] = '-';
    ByteToString(mBytes[8], &string[19]);
    ByteToString(mBytes[9], &string[21]);
    string[23] = '-';
    ByteToString(mBytes[10], &string[24]);
    ByteToString(mBytes[11], &string[26]);
    ByteToString(mBytes[12], &string[28]);
    ByteToString(mBytes[13], &string[30]);
    ByteToString(mBytes[14], &string[32]);
    ByteToString(mBytes[15], &string[34]);
    string[36] = '\0';
    return string;
}
