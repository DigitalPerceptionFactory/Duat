#include "HID.h"


namespace Duat {

	HID* HID::Selection = nullptr;

	void HID::SelectHID()
	{
		Selection = this;
	}

	void HID::ReleaseHID()
	{
		Selection = nullptr;
	}

}