#pragma once
#include "Enumerators.h"


namespace Duat::SSB {
		
	struct Object {
		bool IsGear();
		bool IsConsumable();
		bool IsFurniture();
		bool IsDecoration();

		int m_level;
		float m_durability;
		ObjectType m_type;
	};

}