#pragma once

//EAC ULTRA UD 

extern "C" inline void __CxxFrameHandler4() { __ud2(); }

using strstrf___ = char* (__cdecl*)(const char*, const char*);
inline strstrf___ GetCRT;

using _swprintf___ = int(__cdecl*)(wchar_t*, const wchar_t*, ...);
inline _swprintf___ GetSwprintf;
 
using _sprintf___ = int(__cdecl*)(char*, const char*, ...);
inline _sprintf___ GetSprintf;

using _malloc___ = void*(__cdecl*)(size_t);
inline _malloc___ _malloc;

using _memset___ = void* (__cdecl*)(void*, int, size_t);
inline _memset___ _memset;

inline void* myMemcpy(void* dest, const void* src, unsigned __int64 count)
{
	char* char_dest = (char*)dest;
	char* char_src = (char*)src;
	if ((char_dest <= char_src) || (char_dest >= (char_src + count)))
	{
		while (count > 0)
		{
			*char_dest = *char_src;
			char_dest++;
			char_src++;
			count--;
		}
	}
	else
	{
		char_dest = (char*)dest + count - 1;
		char_src = (char*)src + count - 1;
		while (count > 0)
		{
			*char_dest = *char_src;
			char_dest--;
			char_src--;
			count--;
		}
	}
	return dest;
}


inline size_t m_strlen(const char* str)
{
	const char* p = str;
	while (*p != '\0') {
		++p;
	}
	return p - str;
}

inline size_t m_wstrlen(const wchar_t* str)
{
	const wchar_t* p = str;
	while (*p != '\0') {
		++p;
	}
	return p - str;
}

inline const char* RebuildChar(const char* str, int start, int end, char* buffer, int bufferSize) {
	int length = end - start;

	// Ensure we do not exceed the buffer size
	if (length >= bufferSize) {
		length = bufferSize - 1; // Leave space for null terminator
	}

	// Copy the substring to the buffer
	for (int i = 0; i < length; i++) {
		buffer[i] = str[start + i];
	}

	buffer[length] = '\0'; // Null-terminate the string

	return buffer;
}

inline int FindCharPos(const char* str, char search) {

	int len = m_strlen(str);
	for (int i = 0; i < len; i++)
		if (str[i] == search)
			return i;

	return 0;
}

inline const char* wcharToChar(const wchar_t* wcharStr, char* buffer, size_t bufferSize) {
	size_t i = 0;
	
	// Convert each wide character to char
	while (wcharStr[i] != L'\0' && i < bufferSize - 1) {
		buffer[i] = (char)wcharStr[i]; // Assuming ASCII-compatible characters
		i++;
	}

	// Null-terminate the char string
	buffer[i] = '\0';

	return buffer;
}

inline bool m_wcsicmp(const wchar_t* a, const wchar_t* b) {
	if (!a)
		return false;
	int ret = 0;
	wchar_t* p1 = (wchar_t*)a;
	wchar_t* p2 = (wchar_t*)b;
	while (!(ret = *p1 - *p2) && *p2)
		++p1, ++p2;

	return ret == 0;
}

inline char* __cdecl m_strstr(const char* Str, const char* SubStr)
{
	return GetCRT(Str, SubStr);
}
 

inline unsigned long CustomStrtoul(const char* str, char** endptr, int base)
{
	unsigned long result = 0;
	const char* current = str;

	// Skip leading whitespace
	while (*current == ' ' || *current == '\t' || *current == '\n' || *current == '\r')
		++current;

	// Process characters in the string
	while (*current)
	{
		char c = *current;
		int value = 0;

		if (c >= '0' && c <= '9')
			value = c - '0';
		else if (c >= 'a' && c <= 'f' && base == 16)
			value = c - 'a' + 10;
		else if (c >= 'A' && c <= 'F' && base == 16)
			value = c - 'A' + 10;
		else
			break; // Invalid character for the base

		if (value >= base)
			break; // Character out of range for the base

		result = result * base + value;
		++current;
	}

	if (endptr)
		*endptr = const_cast<char*>(current);

	return result;
}


inline bool m_strcmp(const char* a, char* b) {

	if (!a || !b) return !a && !b;

	int ret = 0;
	unsigned char* p1 = (unsigned char*)a;
	unsigned char* p2 = (unsigned char*)b;
	while (!(ret = *p1 - *p2) && *p2)
		++p1, ++p2;

	return ret == 0;
}

#define RVA(Instr, InstrSize) ((DWORD64)Instr + InstrSize + *(LONG*)((DWORD64)Instr + (InstrSize - sizeof(LONG))))
#define ToLower(Char) ((Char >= 'A' && Char <= 'Z') ? (Char + 32) : Char)
template <typename StrType, typename StrType2>
inline bool StrCmp(StrType Str, StrType2 InStr, bool Two)
{
	if (!Str || !InStr) return false;
	wchar_t c1, c2;
	do
	{
		c1 = *Str++; c2 = *InStr++;
		c1 = ToLower(c1); c2 = ToLower(c2);
		if (!c1 && (Two ? !c2 : 1))
			return true;
	} while (c1 == c2); return false;
}

inline unsigned int m_wcslen(const wchar_t* str)
{
	int cnt = 0;
	if (!str)
		return 0;
	for (; *str != '\0'; ++str)
		++cnt;
	return cnt;
}