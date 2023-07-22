#include "HID.h"


namespace Duat {

	HID* HID::Focus = nullptr;

	void HID::SetFocus()
	{
		Focus = this;
	}

	void HID::ReleaseFocus()
	{
		Focus = nullptr;
	}

}