#include <YAWN/Core/Unicode.hpp>
#include <YAWN/Core/Assert.hpp>

#include <wchar.h>

using namespace YAWN;
//
//int Unicode::Length(const char* utf8) {
//	YAWN_ASSERT(utf8);
//
//	int length = 0;
//
//	for (int offset = 0; utf8[offset];) {
//		if (!(utf8[0] & 0x80)) { // 0xxxxxxx
//			++length;
//			++offset;
//		} else if ((utf8[0] & 0xE0) == 0xC0) { // 110xxxxx
//			++length;
//			offset += 2;
//		} else if ((utf8[0] & 0xF0) == 0xE0) { // 1110xxxx
//			++length;
//			offset += 3;
//		} else {
//			YAWN_ASSERT(0);
//		}
//	}
//
//	return length;
//}
//
//int Unicode::ToUTF32(char32_t& utf32, const char* utf8) {
//	if (!(utf8[0] & 0x80)) { // 0xxxxxxx
//		utf32 = (char32_t)utf8[0];
//		return 1;
//	} else if ((utf8[0] & 0xE0) == 0xC0) { // 110xxxxx
//		utf32 = (char32_t)(((utf8[0] & 0x1F) << 6) | (utf8[1] & 0x3F));
//		return 2;
//	} else if ((utf8[0] & 0xF0) == 0xE0) { // 1110xxxx
//		utf32 = (char32_t)(((utf8[0] & 0x0F) << 12) | ((utf8[1] & 0x3F) << 6) | (utf8[2] & 0x3F));
//		return 3;
//	}
//
//	return 0;
//}
//
//int Unicode::ToUTF8(char* utf8, const char32_t utf32) {
//	char* ptr = utf8;
//	if (utf32 <= 0x7F) {
//		*ptr++ = (char)utf32;
//	} else if (utf32 <= 0x7FF) {
//		*ptr++ = 0xC0 | (char)((utf32 >> 6) & 0x1F);
//		*ptr++ = 0x80 | (char)(utf32 & 0x3F);
//	} else {
//		*ptr++ = 0xE0 | (char)((utf32 >> 12) & 0x0F);
//		*ptr++ = 0x80 | (char)((utf32 >> 6) & 0x3F);
//		*ptr++ = 0x80 | (char)(utf32 & 0x3F);
//	}
//	*ptr = 0;
//	return int(ptr - utf8);
//}
//
//void Unicode::ToUTF32(char32_t* utf32, const char* utf8, int length) {
//	int offset = 0;
//    for (int i = 0; i < length; ++i) {
//		int size = ToUTF32(utf32[i], &utf8[offset]);
//		YAWN_ASSERT(size > 0);
//		offset += size;
//    }
//}
//
//int Unicode::ToUTF8(char* utf8, const char32_t* utf32, int length) {
//	int offset = 0;
//	for (int i = 0; i < length; ++i) {
//		int size = ToUTF8(&utf8[offset], utf32[i]);
//		YAWN_ASSERT(size > 0);
//		offset += size;
//	}
//	return offset;
//}
//
//void Unicode::ToUTF8(char* utf8, const wchar_t* wide, int length) {
//	int offset = 0;
//	for (int i = 0; i < length; ++i) {
//		unsigned char ch = static_cast<unsigned char>(utf8[i]);
//	}
//}
//
//int Unicode::Compare(const char32_t* str1, const char32_t* str2, int length) {
//	for (int i = 0; i < length; ++i) {
//		if (str1[i] != str2[i]) {
//			return str1[i] - str2[i];
//		}
//	}
//
//	return 0;
//}
//
//int Unicode::Compare(const wchar_t* str1, const wchar_t* str2, int length) {
//	return wcsncmp(str1, str2, size_t(length));
//}
