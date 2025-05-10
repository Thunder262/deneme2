#pragma comment(linker, "/MERGE:.CRT=INIT")
#include "Imports.h"

 
inline bool InitCheat()
{

    GameAssembly = (DWORD64)MemUtils::ModuleBase(_("GameAssembly.dll"));
    if (!GameAssembly)
        return false;

    GetCRT = (strstrf___)MemUtils::GetExport((DWORD64)MemUtils::ModuleBase(_("ucrtbase.dll")), _("strstr"));
    GetSwprintf = (_swprintf___)MemUtils::GetExport((DWORD64)MemUtils::ModuleBase(_("msvcrt.dll")), _("swprintf"));
    GetSprintf = (_sprintf___)MemUtils::GetExport((DWORD64)MemUtils::ModuleBase(_("msvcrt.dll")), _("sprintf"));
    _malloc = (_malloc___)MemUtils::GetExport((DWORD64)MemUtils::ModuleBase(_("msvcrt.dll")), _("malloc"));
    _memset = (_memset___)MemUtils::GetExport((DWORD64)MemUtils::ModuleBase(_("msvcrt.dll")), _("memset"));
    
    il2cpp::Init();
    Unity::Methods::Init();
    Dump::Init();
    Hooks::Init(); 
    return true;
}

bool DllMain(uintptr_t hmodule)
{ 
    return InitCheat();
}