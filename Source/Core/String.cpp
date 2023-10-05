#include <YAWN/Core/String.hpp>
#include <YAWN/Core/Memory.hpp>
#include <YAWN/Core/Unicode.hpp>
#include <YAWN/Core/FNV1a.hpp>

#include <string.h>
#include <wchar.h>
#include <stdio.h>
#include <stdarg.h>

using namespace YAWN;

static thread_local wchar_t sBuffer[2048];

String String::FromUTF8(const char* utf8) {
    mbstate_t state = mbstate_t();

    String string;
    string.mSize = int(mbsrtowcs(nullptr, &utf8, 0, &state));
    if (string.mSize > 0) {
        string.mString = (wchar_t*)Memory::Allocate(sizeof(wchar_t) * (string.mSize + 1));

        mbsrtowcs(string.mString, &utf8, size_t(string.mSize), &state);

        string.mString[string.mSize] = 0;
    }

    return string;
}

String String::Format(const wchar_t* format, ...) {
    va_list args;
    va_start(args, format);

#ifdef _MSC_VER
    vswprintf(sBuffer, 2048, format, args);
#else
    vswprintf(sBuffer, format, args);
#endif

    va_end(args);

    return sBuffer;
}

String String::Format(const String& format, ...) {
    va_list args;
    va_start(args, &format);

#ifdef _MSC_VER
    vswprintf(sBuffer, 2048, format.GetData(), args);
#else
    vswprintf(sBuffer, format.GetData(), args);
#endif

    va_end(args);

    return sBuffer;
}

String::String(const wchar_t* string)
    : mSize(string ? int(wcslen(string)) : 0) {
    if (mSize > 0) {
        mString = (wchar_t*)Memory::Allocate(sizeof(wchar_t) * (mSize + 1));

        Memory::Copy(mString, string, sizeof(wchar_t) * (mSize + 1));
    }
}

String::String(const wchar_t* string, int size)
    : mSize(size) {
    if (mSize > 0) {
        mString = (wchar_t*)Memory::Allocate(sizeof(wchar_t) * (mSize + 1));

        Memory::Copy(mString, string, sizeof(wchar_t) * (mSize));

        mString[size] = 0;
    }
}

String::String(const String& string) : mSize(string.mSize) {
    if (mSize > 0) {
        mString = (wchar_t*)Memory::Allocate(sizeof(wchar_t) * (mSize + 1));

        Memory::Copy(mString, string.mString, sizeof(wchar_t) * (mSize + 1));
    }
}

String::String(String&& string) noexcept {
    mString = string.mString;
    mSize = string.mSize;

    string.mString = nullptr;
    string.mSize = 0;
}

String::~String() {
    Memory::Deallocate(mString);
}

String& String::operator=(const wchar_t* string) {
    int size = string ? int(wcslen(string)) : 0;

    if (size > mSize) {
        mString = (wchar_t*)Memory::Reallocate(mString, sizeof(wchar_t) * (size + 1));
    }

    mSize = size;

    if (mSize > 0) {
        Memory::Copy(mString, string, sizeof(wchar_t) * (mSize + 1));
    }

    return *this;
}

String& String::operator=(const String& string) {
    if (string.mSize > mSize) {
        mString = (wchar_t*)Memory::Reallocate(mString, sizeof(wchar_t) * (string.mSize + 1));
    }

    mSize = string.mSize;

    if (mSize > 0) {
        Memory::Copy(mString, string.mString, sizeof(wchar_t) * (mSize + 1));
    }

    return *this;
}

String& String::operator=(String&& string) noexcept {
    Memory::Deallocate(mString);

    mString = string.mString;
    mSize = string.mSize;

    string.mString = nullptr;
    string.mSize = 0;
    return *this;
}

const wchar_t& String::operator[](int index) const {
    YAWN_ASSERT(index >= 0 && index < mSize);

    return mString[index];
}

wchar_t& String::operator[](int index) {
    YAWN_ASSERT(index >= 0 && index < mSize);

    return mString[index];
}

bool String::operator==(const String& string) const {
    if (mSize != string.GetSize()) {
        return false;
    }

    return wcsncmp(GetData(), string.GetData(), size_t(mSize)) == 0;
}

bool String::operator!=(const String& string) const {
    if (mSize != string.GetSize()) {
        return true;
    }

    return wcsncmp(GetData(), string.GetData(), size_t(mSize)) != 0;
}

bool String::operator>(const String& string) const {
    if (mSize != string.GetSize()) {
        return mSize > string.GetSize();
    }

    return wcsncmp(GetData(), string.GetData(), size_t(mSize)) > 0;
}

String String::operator+(const String& string) const {
    String output;

    output.mSize = mSize + string.GetSize();
    if (output.mSize > 0) {
        output.mString = (wchar_t*)Memory::Allocate(sizeof(wchar_t) * (output.mSize + 1));
        memcpy(output.mString, GetData(), mSize * sizeof(wchar_t));
        memcpy(output.mString + mSize, string.GetData(), string.GetSize() * sizeof(wchar_t));
        output.mString[output.mSize] = 0;
    }

    return output;
}

int String::Find(wchar_t character) const {
    for (int i = 0; i < mSize; ++i) {
        if (mString[i] == character) {
            return i;
        }
    }

    return -1;
}

int String::FindLast(wchar_t character) const {
    for (int i = mSize - 1; i >= 0; --i) {
        if (mString[i] == character) {
            return i;
        }
    }

    return -1;
}

String String::Substring(int startIndex, int length) const {
    YAWN_ASSERT(startIndex >= 0 && startIndex < mSize);
    YAWN_ASSERT(length < 0 || startIndex + length < mSize);

    if (length > -1) {
        return String(mString + startIndex, length);
    }

    return String(mString + startIndex, mSize - startIndex);
}

String String::Replace(wchar_t from, wchar_t to) const {
    String string = *this;
    for (int i = 0; i < mSize; ++i) {
        if (string[i] == from) {
            string[i] = to;
        }
    }
    return string;
}

Array<String> String::Split(wchar_t splitter, bool includeEmpty) const {
    Array<String> parts;
    Array<wchar_t> part;

    for (int i = 0; i < mSize; ++i) {
        if (mString[i] == splitter) {
            if (includeEmpty || !part.IsEmpty()) {
                parts.Add(String(part.GetData(), part.GetSize()));
                part.Clear();
            }
        } else {
            part.Add(mString[i]);
        }
    }

    if (includeEmpty || !part.IsEmpty()) {
        parts.Add(String(part.GetData(), part.GetSize()));
    }

    return parts;
}

Array<String> String::Tokenize(const ArrayView<const wchar_t>& splitters, const ArrayView<const wchar_t>& whitespaces, bool includeQuotes) const {
    Array<String> tokens;

    Array<wchar_t> token;
    bool inQuote = false;

    for (int i = 0; i < mSize; ++i) {
        if (mString[i] == '"') {
            if (includeQuotes) {
                token.Add(U'"');
            }

            inQuote = !inQuote;
        } else if (int index = splitters.Find(mString[i]); index > -1) {
            if (inQuote) {
                token.Add(mString[i]);
            } else {
                if (!token.IsEmpty()) {
                    tokens.Add(String(token.GetData(), token.GetSize()));
                    token.Clear();
                }

                tokens.Add(String(&mString[i], 1));
            }
        } else if (int index = whitespaces.Find(mString[i]); index > -1) {
            if (inQuote) {
                token.Add(mString[i]);
            } else if (!token.IsEmpty()) {
                tokens.Add(String(token.GetData(), token.GetSize()));
                token.Clear();
            }
        } else {
            token.Add(mString[i]);
        }
    }

    if (!token.IsEmpty()) {
        tokens.Add(String(token.GetData(), token.GetSize()));
    }

    return tokens;
}

Array<char> String::ToUTF8() const {
    mbstate_t state = mbstate_t();

    const wchar_t* wstr = GetData();
    Array<char> output(int(wcsrtombs(nullptr, &wstr, 0, &state)) + 1);

    wcsrtombs(output.GetData(), &wstr, size_t(output.GetSize()), &state);

    return output;
}

bool String::IsNumeric() const {
    for (int i = 0; i < mSize; ++i) {
        if (mString[i] < '0' || mString[i] > '9') {
            return false;
        }
    }

    return true;
}

bool String::IsDecimal() const {
    for (int i = 0; i < mSize; ++i) {
        if ((mString[i] < L'0' || mString[i] > L'9') && mString[i] != L'.') {
            return false;
        }
    }

    return true;
}

const wchar_t* String::GetData() const { 
    return mString ? mString : L"";
}

bool String::IsEmpty() const {
    return mSize == 0;
}

int String::GetSize() const { 
    return mSize; 
}

int String::GetHash() const {
    return FNV1a::Hash(GetData(), GetSize());
}
