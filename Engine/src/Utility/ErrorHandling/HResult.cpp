#include "HResult.h"

namespace Duat::Utility {

	void HResult::operator<<(HError e)
	{
		if (FAILED(e.hr))
		{
			_com_error ce(e.hr);
			std::basic_string<TCHAR> tstring(ce.ErrorMessage());

			std::string msg =
				std::string(tstring.begin(), tstring.end()) + "\n\n" +
				"Function : " + e.loc.function_name() + "\n" +
				"File : " + e.loc.file_name() + "\n" +
				"Line : " + std::to_string(e.loc.line());

			MessageBoxA(NULL, msg.c_str(), "Error", MB_ICONERROR);
			exit(0);
		}
	}

}