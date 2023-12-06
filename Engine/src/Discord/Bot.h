#pragma once
#include <tuple>
#include <iterator>
#include <string>
#include <dpp/dpp.h>
#include "DiscordMacros.h"
#include "Hangul.h"
#include <Utility/Classes.h>
#include "Command.h"
#include "Message.h"
#include "User.h"
#include "Modal.h"
#include "Select.h"


namespace Duat::Discord {

	struct Bot : dpp::cluster {
		struct Cache {
			int traffic;
			int guild_count;
			int max_guild_count;
		};

		Bot(std::string name, std::string token, uint32_t intents = dpp::i_all_intents);
		~Bot();

		void AddCommand(std::string name, std::string description,
			std::function<void(const dpp::slashcommand_t& event)> fp,
			dpp::slashcommand_contextmenu_type type = dpp::ctxm_chat_input
		);
		void AddCommand(Command cmd);

		void RegisterEvents();

		void           add_buttons(std::vector<Button> buttons);
		int            add_user(const dpp::user& user);
		void           add_to_scoreboard(const dpp::user& user);
		int            get_user_index(dpp::snowflake user_id);
		std::wstring   generate_random_hangul(int number_of_letters);
		bool           is_hangul(const std::string& text);

		
		//ECS::Entity*   e;
		std::string    bot_name;
		std::string    bot_token;
		Cache cache;

		std::vector<Command> m_commands;
		std::map<std::string,Button> m_buttons;
		std::vector<Modal> m_modals;
		std::map<std::string,dpp::emoji> m_emojis;
		
		//std::vector<dpp::user> user_list;
		//std::vector<int>  scoreboard;
		//std::vector<ScoreData>  m_scoreboard;

		int               image_limit;
		bool              board_draw_request;
		dpp::snowflake    init_channel;
		dpp::snowflake    init_guild;
		dpp::snowflake    init_msg;
		dpp::thread       free_thread;
		UINT              practice_thread_count;

		std::vector<std::pair<std::string, std::string>> anki;
		std::map<std::tuple<int, int>, std::string> htsk;

		dpp::snowflake overlord = 335933426295111683;
	};

}