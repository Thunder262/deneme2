#pragma once

#ifndef PerformanceUI_UPDATE
#define PerformanceUI_UPDATE

#include "../../Imports.h"

namespace PerformanceUI {
	inline auto Orig = reinterpret_cast<void (*)(uintptr_t*)>(0);
	void Update(uintptr_t* ui);
}

#endif // !PerformanceUI_UPDATE
