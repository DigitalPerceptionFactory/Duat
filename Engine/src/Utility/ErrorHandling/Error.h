#pragma once
#include <string>
#include <winerror.h>
#include <source_location>
#include <utility>


namespace Duat::Utility {

	struct Error {
		Error(const std::string& message, std::source_location loc = std::source_location::current());
		Error(const char* const& message, std::source_location loc = std::source_location::current());
		std::source_location loc;
		std::string msg = "";
	};

}