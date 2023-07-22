#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <Utility/ErrorHandling.h>


namespace Duat {

	template<typename T>
	std::vector<T> LoadFileAsArray(const std::filesystem::path& path)
	{
		if (std::filesystem::exists(path))
		{
			std::fstream _in;
			_in.open(path, std::ios::in | std::ios::binary);

			std::vector<T> temp;
			if (_in.is_open())
			{
				std::streampos _startPos = _in.tellg();
				_in.seekg(0, std::ios::end);
				int _fileSize = _in.tellg() - _startPos;

				int _elementCount = _fileSize / sizeof(T);
				temp.resize(_elementCount);

				_in.seekg(0);
				_in.read((char*)temp.data(), _fileSize);
				_in.close();
			}
			else {
				Utility::Result result;
				result << "Failed to open file \"" + path.filename().string() + "\"";
			}
			return temp;
		}
		else {
			Utility::Result result;
			result << "Path \"" + path.string() + "\" doesn't exist.";
		}
	}

	template<typename T>
	void SaveFileAsArray(const std::vector<T>& data, const std::filesystem::path& path)
	{
		if (std::filesystem::exists(path))
		{
			std::fstream _out;
			_out.open(path, std::ios::out | std::ios::binary);

			_out.write((char*)data.data(), sizeof(T) * data.size());
			_out.close();
		}
		else
		{
			Utility::Result result;
			result << "Path \"" + path.string() + "\" doesn't exist.";
		}
	}

	template<typename T>
	T LoadFile(const std::filesystem::path& path) { return LoadFileAsArray<T>(path)[0]; }

	template<typename T>
	void SaveFile(T data, const std::filesystem::path& path) { SaveFileAsArray<T>({ data }, path); }

	std::string LoadFileTxt(const std::filesystem::path& path);
	void SaveFileTxt(const std::string& text, const std::filesystem::path& path);

}