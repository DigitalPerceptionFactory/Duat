#pragma once
#include <string>


namespace Duat {

	template<typename T>
	std::string Serialize(const T& data) {
		std::string out;
		out.resize(sizeof(T));
		std::memcpy(out.data(), &data, sizeof(T));
		return out;
	}

	template<typename T>
	T Deserialize(const std::string& data) {
		T out;
		std::memcpy(&out, data.data(), sizeof(T));
		return out;
	}

}