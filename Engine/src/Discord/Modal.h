#pragma once
#include <dpp/dpp.h>

namespace Duat::Discord {

	struct Modal : public dpp::interaction_modal_response
	{
		Modal() = default;
		Modal(std::string title, std::string custom_id, std::function<void(const dpp::form_submit_t& event)> task)
		{
			set_title(title);
			set_custom_id(custom_id);
		}

		void AddRow(std::vector<dpp::component> row_components)
		{
			add_row();
			for (auto& c : row_components) add_component(c);
		}

		std::function<void(const dpp::form_submit_t& event)> task;
	};

}