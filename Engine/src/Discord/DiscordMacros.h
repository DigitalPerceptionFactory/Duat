#pragma once

// name of bot object to capture


#define EVENT_msg           [this](const dpp::message_create_t& event)

#define EVENT_slashcommand  [this](const dpp::slashcommand_t& event)

#define EVENT_ready         [this](const dpp::ready_t& event)

#define EVENT_button        [this](const dpp::button_click_t& event)

#define EVENT_form          [this](const dpp::form_submit_t& event)

#define EVENT_completion    [this](const dpp::confirmation_callback_t& event)





//			
//			pDiscordBot->on_message_create([this](const dpp::message_create_t& event) {
//			
//				if (event.msg.content == "init")
//				{
//					this->m_msg->id = event.msg.id;
//					this->m_msg->channel_id = event.msg.channel_id;
//					this->m_msg->guild_id = event.msg.guild_id;
//				}
//				}
//			);
//			
//			pDiscordBot->on_slashcommand([this](const dpp::slashcommand_t& event) {
//				if (event.command.get_command_name() == "update") {
//					this->m_msg->attachments.clear();
//			
//					std::string value = std::get<std::string>(event.get_parameter("emotion"));
//			
//					if (value == "a")
//						this->m_msg->add_file("neutral.png", dpp::utility::read_file("neutral.png"));
//					else if (value == "b")
//						this->m_msg->add_file("happy.png", dpp::utility::read_file("happy.png"));
//					else if (value == "c")
//						this->m_msg->add_file("sad.png", dpp::utility::read_file("sad.png"));
//			
//					this->pDiscordBot->message_edit(*(this->m_msg));
//				}
//				else if (event.command.get_command_name() == "upload") {
//					this->m_msg->content = "init";
//					this->m_msg->channel_id = event.command.channel_id;
//					this->m_msg->add_file("neutral.png", dpp::utility::read_file("neutral.png"));
//			
//					this->pDiscordBot->message_create(*(this->m_msg));
//				}
//				});
//			
//			pDiscordBot->on_ready([this](const dpp::ready_t& event) {
//				if (dpp::run_once<struct register_bot_commands>()) {
//					this->pDiscordBot->global_command_create(dpp::slashcommand("upload", "Init image.", this->pDiscordBot->me.id));
//			
//					this->pDiscordBot->global_command_create(dpp::slashcommand("update", "Update face emotion.", this->pDiscordBot->me.id).add_option(
//						dpp::command_option(dpp::co_string, "emotion", "choose emotion", true).
//						add_choice(dpp::command_option_choice("neutral", std::string("a"))).
//						add_choice(dpp::command_option_choice("happy", std::string("b"))).
//						add_choice(dpp::command_option_choice("sad", std::string("c")))
//					)
//					);
//				}
//				}
//			);
//			//pDiscordBot->start(1);




					//dpp::slashcommand cmdFont = dpp::slashcommand("cute_set_font", "Set your custom font color.", this->me.id);
					//cmdFont.add_option(dpp::command_option(dpp::co_integer, "R", "RED (0-255)", 1));
					//cmdFont.add_option(dpp::command_option(dpp::co_integer, "G", "GREEN (0-255)", 1));
					//cmdFont.add_option(dpp::command_option(dpp::co_integer, "B", "BLUE (0-255)", 1));
					//cmdFont.add_option(dpp::command_option(dpp::co_integer, "A", "ALPHA (0-255)", 1));

					//dpp::slashcommand cmdBackground = dpp::slashcommand("cute_set_background", "Set your custom background color.", this->me.id);
					//cmdBackground.add_option(dpp::command_option(dpp::co_integer, "R", "RED (0-255)", 1));
					//cmdBackground.add_option(dpp::command_option(dpp::co_integer, "G", "GREEN (0-255)", 1));
					//cmdBackground.add_option(dpp::command_option(dpp::co_integer, "B", "BLUE (0-255)", 1));
					//cmdBackground.add_option(dpp::command_option(dpp::co_integer, "A", "ALPHA (0-255)", 1));

					//this->global_command_create(cmdFont);
					//this->global_command_create(cmdBackground);

					//this->global_command_create(dpp::slashcommand("init", "Bind bot to this channel.", this->me.id));
					//this->global_command_create(dpp::slashcommand("cute_deinit", "Unbind bot from this channel.", this->me.id));
					//this->global_command_create(dpp::slashcommand("cute_practice_start", "Start practice.", this->me.id));
					//this->global_command_create(dpp::slashcommand("cute_practice_stop", "Stop practice.", this->me.id));
					//this->global_command_create(dpp::slashcommand("cute_race_start", "Start race.", this->me.id));
					//this->global_command_create(dpp::slashcommand("cute_race_stop", "Stop race.", this->me.id));

					/*this->global_command_create(dpp::slashcommand("update", "Update face emotion.", this->me.id).add_option(
							dpp::command_option(dpp::co_string, "emotion", "choose emotion", true).
							add_choice(dpp::command_option_choice("neutral", std::string("a"))).
							add_choice(dpp::command_option_choice("happy", std::string("b"))).
							add_choice(dpp::command_option_choice("sad", std::string("c")))
						)
					);*/
