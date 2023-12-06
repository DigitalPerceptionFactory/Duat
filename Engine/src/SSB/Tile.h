#pragma once
#include "Enumerators.h"


namespace Duat::SSB {
	
	struct Tile {
		int m_id;
		int m_owner;
		int m_level;
		// durability increases with world timer
		// if max durability and level less than affinity, then tile level goes up
		float m_durability;

		// affinity levels
		int fire; // higher quality minerals
		int water; // higher quality liquids
		int earth; // higher quality soil
		int air; // higher quality gases
		int holy; // higher quality holy structures
		int cursed; // higher quality cursed structures

		TileType m_type;
	};

}