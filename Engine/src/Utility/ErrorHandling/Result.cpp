#include "Result.h"

namespace Duat::Utility {

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