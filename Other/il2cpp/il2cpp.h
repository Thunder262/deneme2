#pragma once

typedef const char* (*il2cpp_method_get_param_name)(DWORD64, uint32_t);
typedef const char* (*il2cpp_method_get_name)(DWORD64);
typedef int(*GPC)(DWORD64);
typedef DWORD64(*AGI)(DWORD64);
typedef DWORD64(*resolve)(const char*);
typedef DWORD64(*Dm)();
typedef DWORD64(*CFN)(DWORD64, const char*, const char*);
typedef DWORD64(*Call)(DWORD64, DWORD64);
typedef DWORD64(*Ptr)(DWORD64, DWORD64*);
typedef DWORD64* (*DGA)(void*, DWORD64*);

namespace il2cpp
{
	inline il2cpp_method_get_param_name method_get_param_name = 0;
	inline il2cpp_method_get_name method_get_name = 0;
	inline Ptr class_get_methods = 0;
	inline Ptr class_get_fields = 0;
	inline Dm domain_get = 0;
	inline Dm thread_attach = 0;
	inline DGA domain_get_assemblies = 0;
	inline AGI assembly_get_image = 0;
	inline CFN class_from_name = 0;
	inline AGI field_get_offset = 0;
	inline Ptr field_static_get_value = 0;
	inline GPC method_get_param_count = 0;
	inline Call array_new = 0;
	inline resolve new_string = 0;
	inline AGI type_get_object = 0;
	inline AGI class_get_type = 0;
	inline resolve resolve_icall = 0;
	inline AGI object_new = 0;
	inline AGI runtime_class_init = 0;

	inline void Init()
	{
		runtime_class_init = (AGI)(MemUtils::GetExport(GameAssembly, _("il2cpp_runtime_class_init")));
		method_get_param_name = (il2cpp_method_get_param_name)(MemUtils::GetExport(GameAssembly, _("il2cpp_method_get_param_name")));
		method_get_name = (il2cpp_method_get_name)(MemUtils::GetExport(GameAssembly, _("il2cpp_method_get_name")));
		class_get_methods = (Ptr)(MemUtils::GetExport(GameAssembly, _("il2cpp_class_get_methods")));
		class_get_fields = (Ptr)(MemUtils::GetExport(GameAssembly, _("il2cpp_class_get_fields")));
		domain_get = (Dm)(MemUtils::GetExport(GameAssembly, _("il2cpp_domain_get")));
		thread_attach = (Dm)(MemUtils::GetExport(GameAssembly, _("il2cpp_thread_attach")));
		domain_get_assemblies = (DGA)(MemUtils::GetExport(GameAssembly, _("il2cpp_domain_get_assemblies")));
		assembly_get_image = (AGI)(MemUtils::GetExport(GameAssembly, _("il2cpp_assembly_get_image")));
		class_from_name = (CFN)(MemUtils::GetExport(GameAssembly, _("il2cpp_class_from_name")));
		field_get_offset = (AGI)(MemUtils::GetExport(GameAssembly, _("il2cpp_field_get_offset")));
		field_static_get_value = (Ptr)(MemUtils::GetExport(GameAssembly, _("il2cpp_field_static_get_value")));
		method_get_param_count = (GPC)(MemUtils::GetExport(GameAssembly, _("il2cpp_method_get_param_count")));
		array_new = (Call)(MemUtils::GetExport(GameAssembly, _("il2cpp_array_new")));
		new_string = (resolve)(MemUtils::GetExport(GameAssembly, _("il2cpp_string_new")));
		type_get_object = (AGI)(MemUtils::GetExport(GameAssembly, _("il2cpp_type_get_object")));
		class_get_type = (AGI)(MemUtils::GetExport(GameAssembly, _("il2cpp_class_get_type")));
		resolve_icall = (resolve)(MemUtils::GetExport(GameAssembly, _("il2cpp_resolve_icall")));
		object_new = (AGI)(MemUtils::GetExport(GameAssembly, _("il2cpp_object_new")));

	}

	inline DWORD64 InitClass(const char* name, const char* name_space = _("")) {

		DWORD64 domain = domain_get();

		DWORD64 nrofassemblies = 0;
		DWORD64* assemblies;
		assemblies = domain_get_assemblies((void*)domain, &nrofassemblies);

		for (int i = 0; i < nrofassemblies; i++) {
			DWORD64 img = assembly_get_image(assemblies[i]);

			DWORD64 kl = class_from_name(img, name_space, name);
			if (!kl) continue;

			return kl;
		}
		return 0;
	}

	inline DWORD64 TypeGetObject(const char* name_space, const char* name)
	{
		auto klass = InitClass(name, name_space);
		if (!MemUtils::IsValidCheck((void*)klass))
			return 0;

		return type_get_object(class_get_type(klass));
	}

	inline DWORD64 TypeGetObject(uintptr_t klass)
	{
 		return type_get_object(class_get_type(klass));
	}

	inline DWORD64 GetObjectTypeNew(const char* name_space, const char* name)
	{
		auto klass = InitClass(name, name_space);
		return object_new(klass);
	}

	inline DWORD64 Method(const char* kl, const char* name, int argument_number = -1, char* arg_name = _(""), const char* name_space = _(""), int selected_argument = -1) {
		DWORD64 iter = 0;
		auto klass = InitClass(kl, name_space);
		if (MemUtils::IsValidCheck((void*)klass))
		{
			while (DWORD64 f = class_get_methods(klass, &iter)) {
				if (MemUtils::IsValidCheck((void*)f))
				{
					const auto st = method_get_name(f);
					if (MemUtils::IsValidCheck((void*)st))
					{
						if (m_strcmp(st, (char*)name)) {
							if (selected_argument >= 0 && arg_name) {

								int method_count = method_get_param_count(f);
								if (selected_argument > method_count || (argument_number >= 0 && method_count != argument_number)) continue;

								const char* argname;
								if (method_count > 0) {
									argname = method_get_param_name(f, selected_argument - 1);
								}
								else
									argname = (char*)_("-");

								if (!argname || !m_strcmp(argname, arg_name)) continue;
							}

							return f;
						}
					}
				}
			}
		}
		return 0;
	}

	inline DWORD64 Field(DWORD64 klass, char* field_name, bool get_offset = true) {
		DWORD64 out = 0;
		DWORD64 il2cpp_field;

		while (il2cpp_field = class_get_fields(klass, &out)) {

			char* name = (char*)MemUtils::read<DWORD64>(il2cpp_field);
			if (!name)
				break;

			if (!m_strcmp(name, field_name)) {
				continue;
			}
			if (!get_offset)
				return il2cpp_field;

			DWORD64 offset = field_get_offset(il2cpp_field);
			return offset;
		}
		return 0;
	}

	inline DWORD64 GetValue(const char* kl, char* name, bool get_offset = true) {

		auto klass = InitClass(kl);

		if (get_offset) {
			auto field_offset = Field(klass, name);
			return field_offset;
		}
		else
		{
			auto _field = Field(klass, name, false);

			DWORD64 ret;
			field_static_get_value(_field, &ret);
			return ret;
		}
		return 0;
	}

	inline DWORD64 GetOffset(const char* kl, char* name, bool get_offset = true) {

		auto klass = InitClass(kl);
		auto field_offset = Field(klass, name);

		return field_offset;
	}

	inline PBYTE FindPattern(const char* Pattern, const char* Module = nullptr)
	{
		#define InRange(x, a, b) (x >= a && x <= b) 
		#define GetBits(x) (InRange(x, '0', '9') ? (x - '0') : ((x - 'A') + 0xA))
		#define GetByte(x) ((BYTE)(GetBits(x[0]) << 4 | GetBits(x[1])))

		PBYTE ModuleStart = (PBYTE)MemUtils::ModuleBase(Module); if (!ModuleStart) return nullptr;
		PIMAGE_NT_HEADERS NtHeader = ((PIMAGE_NT_HEADERS)(ModuleStart + ((PIMAGE_DOS_HEADER)ModuleStart)->e_lfanew));
		PBYTE ModuleEnd = (PBYTE)(ModuleStart + NtHeader->OptionalHeader.SizeOfImage - 0x1000); ModuleStart += 0x1000;

		PBYTE FirstMatch = nullptr;
		const char* CurPatt = Pattern;
		for (; ModuleStart < ModuleEnd; ++ModuleStart)
		{
			bool SkipByte = (*CurPatt == '\?');
			if (SkipByte || *ModuleStart == GetByte(CurPatt)) {
				if (!FirstMatch) FirstMatch = ModuleStart;
				SkipByte ? CurPatt += 2 : CurPatt += 3;
				if (CurPatt[-1] == 0) return FirstMatch;
			}
			else if (FirstMatch) {
				ModuleStart = FirstMatch;
				FirstMatch = nullptr;
				CurPatt = Pattern;
			}
		}

		return nullptr;
	}
}

inline DWORD64 HookCPP(void* our_func, const char* function_to_hook, const char* class_to_hook, const char* name_space = _(""), int argument_number = -1, char* argument_name = _("")) {
	auto il2cpp_method = il2cpp::Method(class_to_hook, function_to_hook, argument_number, argument_name, name_space);
	*reinterpret_cast<void**>(il2cpp_method) = our_func;
	return il2cpp_method;

}

inline DWORD64 VirtualHook(const char* classname, const char* function_to_hook, void* our_func, const char* name_space = _(""), int argnum = -1, char* argname = _("")) {
	DWORD64 search = *reinterpret_cast<DWORD64*>(il2cpp::Method(classname, function_to_hook, argnum, argname, name_space));
	DWORD64 table = il2cpp::InitClass(classname, name_space);

	if (search == (DWORD64)our_func)
		return (DWORD64)our_func;
	

	for (DWORD64 i = table; i <= table + 0x1500; i += 0x1) {
		DWORD64 addr = *reinterpret_cast<DWORD64*>(i);
		if (addr == search) {
			*reinterpret_cast<DWORD64*>(i) = (DWORD64)our_func;
			return addr;
		}
	}
}
