#include "String.h"
#include <Windows.h>


namespace Duat {

	std::wstring To::WString(const std::string& narrow)
	{
		std::wstring out;
		out.resize(
			MultiByteToWideChar(CP_UTF8, 0, narrow.c_str(), (int)narrow.size(), nullptr, 0)
		);

		// -1 to get null terminated string
		MultiByteToWideChar(CP_UTF8, 0, narrow.c_str(), -1, out.data(), (int)out.size());

		std::wstring normalized;
		int buffer_size = NormalizeString(NORM_FORM::NormalizationC, out.c_str(), (int)out.size(), 0, 0);
		normalized.resize(buffer_size);

		NormalizeString(NORM_FORM::NormalizationC, out.c_str(), -1, normalized.data(), (int)normalized.size());
		return normalized;
	}

	std::string To::String(const std::wstring& wide)
	{
		std::string out;
		out.resize(
			WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), (int)wide.size(), nullptr, 0, NULL, NULL)
		);

		// -1 to get null terminated string
		WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, out.data(), (int)out.size(), NULL, NULL);

		return out;
	}

}