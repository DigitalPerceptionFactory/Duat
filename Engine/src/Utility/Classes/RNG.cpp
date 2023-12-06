#include "RNG.h"


namespace Duat {
		
	float RNG::GetFloat(float from, float to)
	{
		std::random_device dev;
		std::default_random_engine engine(dev());
		std::uniform_real_distribution<float> dist(from, to);
		return dist(engine);
	}

	int RNG::GetInt(int from, int to)
	{
		std::random_device dev;
		std::default_random_engine engine(dev());
		std::uniform_int_distribution<std::default_random_engine::result_type> dist(from, to);
		return dist(engine);
	}

	std::string RNG::GetUUIDString()
	{
		UUID uuid;
		UuidCreate(&uuid);
		char* uuid_ptr;
		UuidToStringA(&uuid, (RPC_CSTR*)&uuid_ptr);
		std::string result(uuid_ptr);
		RpcStringFreeA((RPC_CSTR*)&uuid_ptr);
		return result;
	}

}