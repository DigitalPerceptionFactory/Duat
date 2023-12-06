#pragma once
#include <dpp/dpp.h>

/*

namespace Duat::Discord {

	struct Select : public dpp::component
	{
		Select() = default;
		Select(std::string label, std::string id, std::string placeholder,
			std::vector<std::pair<std::string,std::string>> options,
			std::function<void(const dpp::select_click_t& event)> task = nullptr)
		{
			this->task = task;
			set_type(dpp::cot_selectmenu);
			set_label(label);
			set_id(id);
			set_placeholder(placeholder);

			for (auto& o : options)
				add_select_option(dpp::select_option(o.first, o.second));
		}


		std::function<void(const dpp::select_click_t& event)> task;
	};

}*/