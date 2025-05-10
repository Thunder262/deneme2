#include "Hooks.h"

void Hooks::Init() {

    /*PerformanceUI idk why but with il2cpp method it get throw exception on return origs lol*/
    PerformanceUI::Orig = reinterpret_cast<void(*)(uintptr_t*)>(MemUtils::SignatureScan(GameAssembly, _("40 55 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 80 3D ? ? ? ? ? 48 8B F9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? F0 83 0C 24 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? F0 83 0C 24 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? F0 83 0C 24 ? C6 05")));
  	HookCPP(&PerformanceUI::Update, _("Update"), _("PerformanceUI"), _("Facepunch"), 0);
    HookCPP(&DevControls::OnGUI, _("OnGUI"), _("DevControls"), _(""), 0);
}