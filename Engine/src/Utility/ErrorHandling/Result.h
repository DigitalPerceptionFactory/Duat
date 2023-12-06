#pragma once
#include <string>
#include "Error.h"


namespace Duat::Utility {

	struct Result {
		static void Throw(std::string msg, std::source_location loc = std::source_location::current());
		void operator<<(Error e);
	};

}
