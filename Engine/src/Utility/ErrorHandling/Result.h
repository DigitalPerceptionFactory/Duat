#pragma once
#include <string>
#include <string_view>
#include "Error.h"
#include <comdef.h>


namespace Duat::Utility {

	struct Result {
		static void Throw(std::string msg, std::source_location loc = std::source_location::current());
		void operator<<(Error e);
	};

}
