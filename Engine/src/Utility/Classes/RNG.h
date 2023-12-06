#pragma once
#include <random>
#include <string>
#include <rpc.h>


#pragma comment(lib, "rpcrt4.lib")
namespace Duat {

	struct RNG {
		static float GetFloat(float from, float to);
		static int GetInt(int from, int to);
		static std::string GetUUIDString();
	};

}