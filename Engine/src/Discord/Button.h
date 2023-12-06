#pragma once
#include <dpp/dpp.h>


namespace Duat::Discord {

	struct Button : public dpp::component
	{
		Button() = default;
		Button(std::string label, std::string id, dpp::component_style style, dpp::emoji emoji,
			std::function<void(const dpp::button_click_t& event)> task = nullptr, std::string url = "")
		{
			this->task = task;
			set_type(dpp::cot_button);
			set_style(style);
			set_label(label);
			set_id(id);
			if(url != "") set_url(url);
			if (emoji.name != "") set_emoji(emoji.name, emoji.id, emoji.is_animated());
		}
		Button(std::string label, std::string id, dpp::component_style style, std::string unicode_emoji = "",
			std::function<void(const dpp::button_click_t& event)> task = nullptr, std::string url = "")
		{
			this->task = task;
			set_type(dpp::cot_button);
			set_style(style);
			set_label(label);
			set_id(id);
			if (url != "") set_url(url);
			if (emoji.name != "") set_emoji(unicode_emoji);
		}

		std::function<void(const dpp::button_click_t& event)> task;
	};

}