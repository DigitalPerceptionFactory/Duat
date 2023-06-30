#pragma once
#include <string>
#include <string_view>
#include "Error.h"
#include <comdef.h>


namespace Duat::Utility {

	struct Result {
		void operator<<(Error e);
	};

}
