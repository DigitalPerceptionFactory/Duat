#include "Loader.h"


namespace Duat {

	std::string LoadFileTxt(const std::filesystem::path& path)
	{
		auto vec = LoadFileAsArray<char>(path);
		return std::string(vec.begin(), vec.end());
	}

	void SaveFileTxt(const std::string& text, const std::filesystem::path& path)
	{
		std::vector<char> data(text.begin(), text.end());
		SaveFileAsArray(data, path);
	}
}