#include "Error.h"

namespace Duat::Utility {
		
	Error::Error(const std::string& message, std::source_location loc) : loc(std::move(loc))
	{
		msg = message;
	}

	Error::Error(const char* const& message, std::source_location loc) : loc(std::move(loc))
	{
		msg = message;
	}
}