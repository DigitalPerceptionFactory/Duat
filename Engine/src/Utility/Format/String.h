#pragma once
#include <string>


namespace Duat {

	struct To {
		static std::wstring WString(const std::string& narrow);
		static std::string String(const std::wstring& wide);
	};

}