#pragma once 

#include "Array.hpp"
#include "ArrayView.hpp"

namespace YAWN {
    class String {
    public:
        static String FromUTF8(const char* utf8);

        static String Format(const wchar_t* format, ...);

        static String Format(const String& format, ...);

        String() = default;

        String(const wchar_t* string);

        String(const wchar_t* string, int size);

        String(const String& string);

        String(String&& string) noexcept;

        ~String();

        String& operator=(const wchar_t* string);

        String& operator=(const String& string);

        String& operator=(String&& string) noexcept;

        const wchar_t& operator[](int index) const;

        wchar_t& operator[](int index);

        bool operator==(const String& string) const;

        bool operator!=(const String& string) const;

        bool operator>(const String& string) const;

        String operator+(const String& string) const;

        int Find(wchar_t character) const;

        int FindLast(wchar_t character) const;

        String Substring(int startIndex, int length = -1) const;

        String Replace(wchar_t from, wchar_t to) const;

        Array<String> Split(wchar_t splitter, bool includeEmpty = false) const;

        Array<String> Tokenize(const ArrayView<const wchar_t>& splitters, const ArrayView<const wchar_t>& whitespaces, bool includeQuotes = false) const;

        Array<char> ToUTF8() const;

        bool IsNumeric() const;

        bool IsDecimal() const;

        const wchar_t* GetData() const;

        bool IsEmpty() const;

        int GetSize() const;

        int GetHash() const;

    private:
        wchar_t* mString = nullptr;
        int mSize = 0;
    };
}
