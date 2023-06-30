#pragma once
#include <string>
#include <winerror.h>
#include <source_location>
#include <utility>


namespace Duat::Utility {

	struct HError {
		HError(HRESULT hr, std::source_location loc = std::source_location::current());
		HRESULT hr;
		std::source_location loc;
	};

}