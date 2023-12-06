#pragma once
#include <string>
#include <source_location>


namespace Duat::Utility {

	struct Error {
		Error(const std::string& message, std::source_location loc = std::source_location::current());
		Error(const char* const& message, std::source_location loc = std::source_location::current());
		std::source_location loc;
		std::string msg = "";
	};

}