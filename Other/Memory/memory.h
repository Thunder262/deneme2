#pragma once

#define InRange(x, a, b) (x >= a && x <= b) 
#define GetBits(x) (InRange(x, '0', '9') ? (x - '0') : ((x - 'A') + 0xA))
#define GetByte(x) ((BYTE)(GetBits(x[0]) << 4 | GetBits(x[1])))

namespace MemUtils {

	template<typename T = uintptr_t, typename A>
	T& read(A address) {
		auto addresss = (DWORD64)address;
		if (addresss > 0x40000 && (addresss + sizeof(T)) < 0x7FFFFFFF0000)
			return *(T*)addresss;

		auto n = nullptr;
		return reinterpret_cast<T&>(n);
	}
	template <typename T>
	void write(uintptr_t address, T data) {
		if (address > 0x40000 && (address + sizeof(T)) < 0x7FFFFFFF0000)
			*(T*)(address) = data;
	}

	inline  PBYTE ModuleBase(const char* ModuleName)
	{
		PPEB_LDR_DATA Ldr = ((PTEB)__readgsqword(FIELD_OFFSET(NT_TIB, Self)))->ProcessEnvironmentBlock->Ldr; void* ModBase = nullptr;
		for (PLIST_ENTRY CurEnt = Ldr->InMemoryOrderModuleList.Flink; CurEnt != &Ldr->InMemoryOrderModuleList; CurEnt = CurEnt->Flink) {
			LDR_DATA_TABLE_ENTRY* pEntry = CONTAINING_RECORD(CurEnt, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
			PUNICODE_STRING BaseDllName = (PUNICODE_STRING)&pEntry->Reserved4[0];
			if (!ModuleName || StrCmp(ModuleName, BaseDllName->Buffer, false))
				return (PBYTE)pEntry->DllBase;
		}

		return nullptr;
	}

	inline ULONG64 GetExport(ULONG64 hDll, const char* Name)
	{
		PIMAGE_NT_HEADERS NT_Head = (PIMAGE_NT_HEADERS)(hDll + ((PIMAGE_DOS_HEADER)hDll)->e_lfanew);
		PIMAGE_EXPORT_DIRECTORY ExportDir = (PIMAGE_EXPORT_DIRECTORY)(hDll + NT_Head->OptionalHeader.DataDirectory[0].VirtualAddress);

		for (DWORD i = 0; i < ExportDir->NumberOfNames; i++)
		{
			USHORT Ordinal = ((USHORT*)(hDll + ExportDir->AddressOfNameOrdinals))[i];
			const char* ExpName = (const char*)hDll + ((DWORD*)(hDll + ExportDir->AddressOfNames))[i];

			for (int i = 0; ExpName[i] == Name[i]; i++) if (!ExpName[i])
				return hDll + ((DWORD*)(hDll + ExportDir->AddressOfFunctions))[Ordinal];
		} return 0;
	}

	inline uintptr_t SignatureScan(uintptr_t _module, const char* pattern)
	{
		uintptr_t moduleAddress = _module;

 		// Convert pattern to byte array manually, avoiding STL.
		auto patternToByte = [](const char* pattern, int* outBytes, int& outSize)
		{
			outSize = 0;
			const char* current = pattern;

			while (*current)
			{
				if (*current == '?')
				{
					outBytes[outSize++] = -1;
					++current;
					if (*current == '?')
						++current;
				}
				else
				{
					char byteStr[3] = { 0 };
					byteStr[0] = *current;
					byteStr[1] = *(current + 1);
					outBytes[outSize++] = CustomStrtoul(byteStr, nullptr, 16);
					current += 2;
				}

				while (*current == ' ') ++current; // Skip spaces.
			}
		};

		const auto dosHeader = (PIMAGE_DOS_HEADER)moduleAddress;
		const auto ntHeaders = (PIMAGE_NT_HEADERS)((uint8_t*)moduleAddress + dosHeader->e_lfanew);

		const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
		auto scanBytes = reinterpret_cast<uint8_t*>(moduleAddress);

		int patternBytes[256]; // Fixed-size array for pattern.
		int patternSize = 0;

		patternToByte(pattern, patternBytes, patternSize);

		for (uintptr_t i = 0; i < sizeOfImage - patternSize; ++i)
		{
			bool found = true;
			for (int j = 0; j < patternSize; ++j)
			{
				if (scanBytes[i + j] != patternBytes[j] && patternBytes[j] != -1)
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				return reinterpret_cast<uintptr_t>(&scanBytes[i]);
			}
		}
		return NULL;
	}

	inline bool IsValidCheck(void* m_pPointer)
	{
		if (reinterpret_cast<DWORD64>(m_pPointer) <= 0x400000 || reinterpret_cast<DWORD64>(m_pPointer) >= 0x7fffffffffff)
			return false;

		return true;
	}
}