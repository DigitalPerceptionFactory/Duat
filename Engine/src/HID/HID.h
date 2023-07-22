#pragma once
#include "Keyboard.h"
#include "Mouse.h"


namespace Duat {

	struct HID {
		static HID* Focus;
		void SetFocus();
		void ReleaseFocus();
		virtual void Interact(Keyboard& kbd, Mouse& mouse) = 0;
	};

}