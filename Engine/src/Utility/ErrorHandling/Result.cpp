#include "Result.h"

namespace Duat::Utility {

	void Result::Throw(std::string msg, std::source_location loc)
	{
		msg += "\n\nFunction : " + std::string(loc.function_name()) + "\n" +
			"File : " + loc.file_name() + "\n" +
			"Line : " + std::to_string(loc.line());
		MessageBoxA(NULL, msg.c_str(), "Error", MB_ICONERROR);
		exit(0);
	}

	void Result::operator<<(Error e)
	{
		if (e.msg != "")
		{
			std::string msg =
				e.msg + "\n\n" +
				"Function : " + e.loc.function_name() + "\n" +
				"File : " + e.loc.file_name() + "\n" +
				"Line : " + std::to_string(e.loc.line());

			MessageBoxA(NULL, msg.c_str(), "Error", MB_ICONERROR);
			exit(0);
		}
	}
}