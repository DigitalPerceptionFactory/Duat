#pragma once
#include <dpp/dpp.h>

namespace Duat::Discord {

	struct Command :public dpp::slashcommand {
		std::function<void(const dpp::slashcommand_t& event)> task;
	};

}