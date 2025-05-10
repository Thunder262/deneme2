#pragma once

#ifndef ONGUI_H
#define ONGUI_H

#include "../../Imports.h"

namespace DevControls {
	inline auto Orig = reinterpret_cast<void (*)(uintptr_t*)>(0);
	void OnGUI(uintptr_t* ui);
}

#endif // !ONGUI_H
