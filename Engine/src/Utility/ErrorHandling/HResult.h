#pragma once
#include <string>
#include <string_view>
#include "HError.h"
#include <comdef.h>


namespace Duat::Utility {

	struct HResult {
		void operator<<(HError e);
	};

}
