#pragma once
#include <vector>
#include "Tile.h"


namespace Duat::SSB {
		
	struct World {
		int m_level;
		WorldType m_type;

		std::vector<std::vector<Tile>> m_tiles;
	};

}