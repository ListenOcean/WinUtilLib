#include "BaseUtil.h"
namespace str {
	size_t Len(const wchar_t* str) {
		if (str == nullptr)
			return -1;
		return wcslen(str);
	}
	size_t Len(const char* str) {
		if (str == nullptr)
			return -1;
		return strlen(str);
	}
	char* Dup(const char* s) {
		return s ? _strdup(s) : nullptr;
	}
	wchar_t* Dup(const wchar_t* s) {
		if (!s)
			return nullptr;
		wchar_t* dst;
		size_t size=wcslen(s)*sizeof(wchar_t);
		dst = (wchar_t*)Allocator::Alloc(nullptr, size+2);
		memcpy(dst, s, size);
		return dst;
	}
	std::wstring& ConcateWstring(std::wstring& dstStr, std::initializer_list<std::wstring> list) {
		for (auto& str : list) {
			dstStr += str;
		}
		return dstStr;
	}
	char* FmtV(const char* fmt, va_list args) {
		char message[256];
		size_t bufCchSize = dimof1(message);
		char* buf = message;
		for (;;) {
			int count = vsnprintf(buf, bufCchSize, fmt, args);
			if ((count >= 0) && ((size_t)count < bufCchSize))
				break;
			/* we have to make the buffer bigger. The algorithm used to calculate
			   the new size is arbitrary*/
			if (buf != message)
				free(buf);
			if (bufCchSize < 4 * 1024)
				bufCchSize += bufCchSize;
			else
				bufCchSize += 1024;
			buf = (char*)Allocator::Alloc(nullptr, bufCchSize);
			if (!buf)
				break;
		}

		if (buf == message)
			buf = str::Dup(message);

		return buf;
	}
	bool IsEmpty(const char* s){
		return !s || *s == 0;
	}
	bool IsEmpty(const wchar_t* s){
		return !s || *s == 0;
	}
}