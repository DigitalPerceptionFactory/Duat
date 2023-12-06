#pragma once
#include "Button.h"
#include <filesystem>


namespace Duat::Discord {

	struct Message : dpp::message {
		Message() = default;
		Message(std::string content, dpp::snowflake channel_id, dpp::snowflake guild_id)
		{
			this->content = content;
			this->channel_id = channel_id;
			this->guild_id = guild_id;
		}
		Message(std::string content, const dpp::slashcommand_t& event, bool is_ephemeral = 0)
		: Message(content, event.command.channel_id, event.command.guild_id)
		{
			if (is_ephemeral)
				set_flags(dpp::m_ephemeral);
		}
		Message(std::string content, const dpp::message_create_t& event, bool is_ephemeral = 0)
		: Message(content, event.msg.channel_id, event.msg.guild_id)
		{
			if (is_ephemeral)
				set_flags(dpp::m_ephemeral);
		}
		Message(std::string content, const dpp::button_click_t& event, bool is_ephemeral = 0)
		: Message::Message(content, event.command.channel_id, event.command.guild_id)
		{
			if (is_ephemeral)
				set_flags(dpp::m_ephemeral);
		}
		Message(std::string content, const dpp::thread& thread, bool is_ephemeral = 0)
			: Message::Message(content, thread.id, thread.guild_id)
		{
			if (is_ephemeral)
				set_flags(dpp::m_ephemeral);
		}

		void SetFile(std::filesystem::path path)
		{
			attachments.clear();
			filecontent.clear();
			add_file(path.filename().string(), dpp::utility::read_file(path.string()));
		}

		void SetFile(std::string upload_name, std::filesystem::path path)
		{
			attachments.clear();
			filecontent.clear();
			add_file(upload_name, dpp::utility::read_file(path.string()));
		}

		std::vector<Button> AddButtons(std::vector<Button> buttons)
		{
			dpp::component base;
			for (auto& b : buttons)
				base.add_component(b);

			add_component(base);
			return buttons;
		}

	};

}