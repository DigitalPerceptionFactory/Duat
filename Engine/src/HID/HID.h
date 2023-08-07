#pragma once
#include "Keyboard.h"
#include "Mouse.h"


namespace Duat {

	struct HID {
		static HID* Selection;
		void SelectHID();
		void ReleaseHID();
		virtual void Interact(Keyboard& kbd, Mouse& mouse) = 0;
	};

}