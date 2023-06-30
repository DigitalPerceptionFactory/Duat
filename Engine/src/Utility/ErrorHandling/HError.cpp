#include "HError.h"

namespace Duat::Utility {

	HError::HError(HRESULT hr, std::source_location loc) : hr(hr), loc(std::move(loc))
	{
	}

}