#include "Bot.h"


namespace Duat::Discord {

	Bot::Bot(std::string name, std::string token, uint32_t intents)
		: dpp::cluster(token, intents)
	{
		cache = { 0 };

		if (!std::filesystem::exists("discord_bot_cache"))
			SaveFile(cache, "discord_bot_cache");
		else if(std::filesystem::file_size("discord_bot_cache") != sizeof(cache))
			SaveFile(cache, "discord_bot_cache");

		cache = LoadFile<Cache>("discord_bot_cache");
		bot_name = name;
		bot_token = token;
		init_channel = 0;
		init_guild = 0;
		m_emojis[""] = dpp::emoji("");
		board_draw_request = true;
		image_limit = 3;
		practice_thread_count = 0;
		//e = new ECS::Entity();
		//Component::CuteUser::record[0] = 99999.0; // push down null component index
		//Component::CuteUser::record_wstring[0] = L"";

		/*for (int i = 0; i < anki_wstring.length() && anki_wstring.find_first_of('\n',i) != std::wstring::npos;
			i = anki_wstring.find_first_of('\n', i) + 1)
		{
			anki.push_back(
				{
					To::MultiByte(
						anki_wstring.substr(
							i,
							anki_wstring.find_first_of('_', i) - i
						)
					),
					To::MultiByte(
						anki_wstring.substr(
							anki_wstring.find_first_of('_', i),
							anki_wstring.find_first_of('\n', i)
						)
					)
				}
			);
		}*/


		/*AddCommand("cutesetup", EVENT_slashcommand)
		{
			// if I am the one who called it
			if (event.command.member.user_id == 335933426295111683)
			{
				for (auto& kv : guild_emojis_get_sync(this->init_guild))
					this->m_emojis[kv.second.name] = kv.second;

				Message msg("", event);
				auto buttons = msg.AddButtons(
				{
					Button("Get Roles!", "setup_button", dpp::cos_primary, this->m_emojis["parrot"],
					EVENT_button
					{

					}
				}
				);
			}
		}
		);*/

		/*AddCommand("cuteinit", EVENT_slashcommand
			{
				// if I am the one who called it
				if (event.command.member.user_id == 335933426295111683)
				{
					if (this->init_channel != 0)
						event.reply(Message("Hangul game already initialized", event, 1));
					else
					{
						this->init_channel = event.command.channel_id;
						this->init_guild = event.command.guild_id;
						// -- delete
						this->free_thread = this->thread_create_sync(
							"cinnamoroll_" + std::to_string(this->practice_thread_count), this->init_channel, 60,
							dpp::channel_type::CHANNEL_PUBLIC_THREAD, 0, 0
						);
						this->practice_thread_count++;
						// -- delete

						for (auto& kv : guild_emojis_get_sync(this->init_guild))
							this->m_emojis[kv.second.name] = kv.second;

						Message msg("", event);
						msg.SetFile("banner.png");

						auto buttons = msg.AddButtons(
							{
								Button("Play", "play_button", dpp::cos_primary, this->m_emojis["play"],
									EVENT_button {
										int index = add_user(event.command.usr);
										auto user = Component::CuteUser::Interface(index);

										user.edit_token = event.command.token;
										user.practice_wstring = generate_random_hangul(3);
										user.practice_counter = 0;
										user.is_participating.value = true;
										user.update_image.value = false;
										user.practice_thread = this->free_thread;
										this->free_thread = this->thread_create_sync(
											"cinnamoroll_" + std::to_string(this->practice_thread_count), this->init_channel, 60,
											dpp::channel_type::CHANNEL_PUBLIC_THREAD, 0, 0
										);
										this->practice_thread_count++;

										//countdown
										Message msg("", user.practice_thread, 1);
										msg.SetFile("3.png");
										event.reply(msg);
										Sleep(1000);

										msg = Message("", user.practice_thread, 0);
										msg.SetFile("2.png");
										//this->interaction_followup_edit_original(user.edit_token, msg);
										Sleep(1000);

										msg = Message("", user.practice_thread, 1);
										msg.SetFile("1.png");
										//this->interaction_followup_edit_original(user.edit_token, msg);
										Sleep(1000);

										user.update_image.value = true;
										user.practice_timer.Start();
									}
								),
								Button("Scoreboard", "score_button", dpp::cos_primary,	this->m_emojis["scoreboard"],
									EVENT_button {
										Message msg("", event, 1);
										msg.SetFile("scoreboard.png");
										event.reply(msg);
									}
								),
								Button("Settings", "settings_button", dpp::cos_primary, "",
									EVENT_button {

										Modal mod("Settings", "settings_modal",
											[](const dpp::form_submit_t& event)
											{
												//event.components[0].components[0].value
											}
										);

										mod.add_component(
											Select("Click me", "buttonid123", "my_placeholder",
												{
													{"choice", "1"}
												})
										);

										// -- delete
									mod.add_component(
										Select("Font", "settings_field_0", "font color",
											{
												{"Black", "1"},
												{"White", "2"},
												{"Dark Grey", "3"},
												{"Light Grey", "4"},
												{"Blue", "5"},
												{"Pink", "6"}
											}
										)
									);

										mod.AddRow({ Select("Font", "settings_field_0", "font color",
												{
													{"Black", "1"},
													{"White", "2"},
													{"Dark Grey", "3"},
													{"Light Grey", "4"},
													{"Blue", "5"},
													{"Pink", "6"}
												}
											)
										});

										mod.AddRow({ Select("Background", "settings_field_1", "background color",
												{
													{"Black", "1"},
													{"White", "2"},
													{"Dark Grey", "3"},
													{"Light Grey", "4"},
													{"Blue", "5"},
													{"Pink", "6"}
												}
											)
										});

										mod.AddRow({ Select("Layout", "settings_field_3", "layout style",
												{
													{"Horizontal", "1"},
													{"Vertical", "2"},
												}
											)
										});
										// -- delete

										event.dialog(mod);
									}
								)
							}
						);

						this->add_buttons(buttons);
						event.reply(msg);
					}
				}
			}
		);*/

		AddCommand("setstatus", "Sets status", EVENT_slashcommand
			{
				//dpp::activity a;
				//a.type = dpp::at_watching;
				//a.name = " servers.";
				dpp::presence p(dpp::presence_status::ps_online, dpp::at_watching, " servers");
				set_presence(p);
			}
		);

		AddCommand("log", "Admin debug command.", EVENT_slashcommand
			{
				if (event.command.member.user_id == overlord)
				{
					set_presence(dpp::presence(dpp::presence_status::ps_online, dpp::at_watching, std::to_string(cache.guild_count) + " servers."));
					Message msg("Traffic: " + std::to_string(cache.traffic) + "\n" +
						"Servers: " + std::to_string(cache.guild_count) + "\n" +
						"Max: " + std::to_string(cache.max_guild_count), event, 1);
					event.reply(msg);
				}
				else
				{
					Message msg("Sorry, you don't have permission to use this command.", event, 1);
					event.reply(msg);
				}
			}
		);
				
		AddCommand("htsk", "Generate random card.", EVENT_slashcommand
			{
				++cache.traffic;
				cache.guild_count = dpp::get_guild_count();
				if (cache.guild_count > cache.max_guild_count)
					cache.max_guild_count = cache.guild_count;
				SaveFileAsArray<Cache>({ cache }, "discord_bot_cache");

				set_presence(dpp::presence(dpp::presence_status::ps_online, dpp::at_watching, std::to_string(cache.guild_count) + " servers."));

				auto it = std::begin(htsk);
				//std::advance(it, RNG(0, htsk.size() - 1));
				auto htsk_pair = *it;
				int lesson = std::get<0>(htsk_pair.first);
				int word = std::get<1>(htsk_pair.first);

				Message msg(htsk_pair.second, event, 1);
				msg.SetFile(std::to_string(word) + ".mp3",
					"htsk_anki/Lesson " + std::to_string(lesson) + "/" + std::to_string(word) + ".mp3");
				
				std::string button_custom_id = "htsk_" + std::to_string(word) + "_" + std::to_string(lesson);
				Button b_post("Post", button_custom_id, dpp::cos_secondary, "",
					[this, htsk_pair, lesson, word](const dpp::button_click_t& event)
					{
						Message post_msg(htsk_pair.second, event, 0);
						post_msg.SetFile(std::to_string(word) + ".mp3",
							"htsk_anki/Lesson " + std::to_string(lesson) + "/" + std::to_string(word) + ".mp3");
						
						this->message_create(post_msg);
						//event.reply(post_msg);
					}
				);
				m_buttons[button_custom_id] = b_post;

				Button b_vote("Vote", "vote", dpp::cos_link);
				b_vote.url = "https://top.gg/bot/993211287679012954/vote";
				Button b_join("Join Support Server", "join", dpp::cos_link);
				b_join.url = "https://discord.gg/P8XMMT9JqQ";
				
				std::vector<Button> buttons;
				buttons.push_back(b_post);
				buttons.push_back(b_vote);
				buttons.push_back(b_join);
								
				msg.AddButtons(buttons);
				
				event.reply(msg);
			}
		);

		RegisterEvents();
		this->start(true);
	}

	Bot::~Bot()
	{
	}

	void Bot::AddCommand(std::string name, std::string description, std::function<void(const dpp::slashcommand_t& event)> task, dpp::slashcommand_contextmenu_type type)
	{
		Command cmd;
		cmd.name = name;
		cmd.description = "no description provided for /" + name;
		cmd.task = task;
		cmd.type = type;
		cmd.description = description;
		cmd.application_id = this->me.id;
		m_commands.push_back(cmd);
	}

	void Bot::AddCommand(Command cmd)
	{
		m_commands.push_back(cmd);
	}

	void Bot::RegisterEvents()
	{
		this->on_log([](const dpp::log_t& event) {
			OutputDebugStringA(event.message.c_str());
			}
		);

		this->on_ready(EVENT_ready
			{
				set_presence(dpp::presence(dpp::presence_status::ps_online, dpp::at_watching, std::to_string(cache.guild_count) + " servers."));
				if (dpp::run_once<struct register_bot_commands>()) {
					std::vector<dpp::slashcommand> vec;
					this->global_bulk_command_create(vec);
										
					for (auto& cmd : m_commands)
						this->global_command_create(cmd);
				}
			}
		);

		this->on_message_create(EVENT_msg
			{

				/*if(event.msg.content.find("<<") != std::string::npos
				&& event.msg.content.find(">>") != std::string::npos)
				{
					size_t time_begin = event.msg.content.find("<<");
					size_t time_end = event.msg.content.find(">>");
					std::string time_string = event.msg.content.substr
					(time_begin, time_end);

					if (
						(time_string[4] == ':')
						&&
						(time_string[2] >= 0 && time_string[2] <= 9)
						&&
						(time_string[3] >= 0 && time_string[3] <= 9)
						&&
						(time_string[5] >= 0 && time_string[5] <= 9)
						&&
						(time_string[6] >= 0 && time_string[6] <= 9)
						&&
						(time_string[7] == '>')
						&&
						(time_string[8] == '>')
						)
					{
						std::string hour = "";
						hour.push_back(time_string[2]);
						hour.push_back(time_string[3]);
						std::string minute = "";
						minute.push_back(time_string[5]);
						minute.push_back(time_string[6]);
					}

					dpp::message new_msg = event.msg;
					new_msg.content.erase(
						new_msg.content.begin() + time_begin,
						new_msg.content.begin() + time_end
					);
					new_msg.content.insert(
						time_begin, "UNIXTIME");
					this->message_edit(new_msg);
				}*/

				if (!event.msg.author.is_bot() && event.msg.channel_id == this->init_channel)
				{
					int index = get_user_index(event.msg.author.id);
					if (index != -1)
					{
						/*
						auto user = Component::CuteUser::Interface(index);
						if (event.msg.content == To::MultiByte(user.practice_wstring))
						{
							if (user.practice_counter == image_limit - 1)
							{
								// you done gg wp
								user.practice_timer.Stop();
								user.practice_counter++;
								user.is_participating.value = false;

								double delta = user.practice_timer.GetDelta();
								if (user.record > delta)
								{
									user.record = delta;
									user.record_wstring = user.practice_timer.ToWide();
								}

								// 11 because im not sure how ECS works now and if it has 0 null element
								if (Component::CuteUser::SIZE <= 11
									||
									(Component::CuteUser::SIZE > 11 &&
										user.record < Component::CuteUser::record[Component::CuteUser::board_position[10]])
									)
								{
									std::sort(
										Component::CuteUser::board_position.begin(),
										Component::CuteUser::board_position.end(),
										[](int a, int b)
										{
											return Component::CuteUser::record[a] < Component::CuteUser::record[b];
										}
									);
									this->board_draw_request = true;
								}
								
								user.update_image.value = true;
							}
							else
							{
								user.practice_counter++;
								user.practice_wstring = generate_random_hangul(3);
								user.update_image.value = true;
							}
						}
						*/
					}

				}
				static int init_message = 0;
				if (event.msg.channel_id == this->init_channel && init_message != 0)
					this->message_delete(event.msg.id, event.msg.channel_id);

				if (init_message < 5)
					++init_message;
			}
		);

		this->on_button_click(EVENT_button
			{
				for (auto& b : m_buttons)
					if (event.custom_id == b.first && b.second.task != nullptr)
						b.second.task(event);
			}
		);

		this->on_form_submit(EVENT_form{

			for (auto& m : m_modals)
				if (event.custom_id == m.custom_id && m.task != nullptr)
					m.task(event);

				if (event.custom_id == "ZZZsettings_modal")
				{

					std::string font = std::get<std::string>(event.components[0].components[0].value);
					std::string background = std::get<std::string>(event.components[1].components[0].value);
					std::string layout = std::get<std::string>(event.components[2].components[0].value);
					int index = get_user_index(event.command.usr.id);

					if (index != -1)
					{
						/*
						auto user = Component::CuteUser::Interface(index);
						if (font == "1") user.brush = { 0,0,0,1 };
						else if (font == "2") user.brush = { 1,1,1,1 };
						else if (font == "3") user.brush = { 0.382,0.382,0.382,1 };
						else if (font == "4") user.brush = { 0.618,0.618,0.618,1 };
						else if (font == "5") user.brush = { 0,0,1,1 };
						else if (font == "6") user.brush = { 1,0.382,0.618,1 };

						if (background == "1") user.background = { 0,0,0,1 };
						else if (background == "2") user.background = { 1,1,1,1 };
						else if (background == "3") user.background = { 0.382,0.382,0.382,1 };
						else if (background == "4") user.background = { 0.618,0.618,0.618,1 };
						else if (background == "5") user.background = { 0,0,1,1 };
						else if (background == "6") user.background = { 1,0.382,0.618,1 };

						if (layout == "horizontal")    user.layout = "horizontal";
						else if (layout == "vertical") user.layout = "vertical";
						*/
					}
				}

			}
		);

		this->on_slashcommand(EVENT_slashcommand
			{
				for (auto& cmd : m_commands)
					if (event.command.get_command_name() == cmd.name)
						cmd.task(event);
			}
		);

	}















	void Bot::add_buttons(std::vector<Button> buttons)
	{
		for (auto& b : buttons)
		{
			m_buttons[b.custom_id] = b;
		}
	}

	int Bot::add_user(const dpp::user& user)
	{
		return 0;
		/*int index = get_user_index(user.id);
		if (index == -1)
		{
			e->AddComponent<Component::CuteUser>();
			auto cute_user = e->GetComponent<Component::CuteUser>(-1);
			cute_user.usr = user;
			cute_user.record = 99999.0;
			cute_user.record_wstring = L"99:99:99";
			cute_user.board_position = Component::CuteUser::SIZE - 1;
			return Component::CuteUser::SIZE - 1;
		}
		else return index;*/
	}

	void Bot::add_to_scoreboard(const dpp::user& user)
	{
		/*for (auto& score_data : m_scoreboard)
			if (score_data.id == user.id) return;

		ScoreData sd;
		sd.id = user.id;
		sd.username = To::Wide(user.username);
		sd.record = 99999.0;
		sd.record_wstring = L"99:99:99";
		m_scoreboard.push_back(sd);*/
	}

	int Bot::get_user_index(dpp::snowflake user_id)
	{
		//for (int i = 0; i < Component::CuteUser::SIZE; ++i)
		//	if (Component::CuteUser::usr[i].id == user_id) return i;

		return -1;
	}

	std::wstring Bot::generate_random_hangul(int number_of_letters)
	{
		//std::random_device dev;
		//std::default_random_engine engine(dev());
		//std::uniform_int_distribution<std::default_random_engine::result_type> dist(44032, 55171);

		std::wstring result;
		result.resize(number_of_letters);

		//for (int i = 0; i < number_of_letters; ++i)
		//	result[i] = dist(engine);

		return result;
	}
	bool Bot::is_hangul(const std::string& text)
	{
		//std::wstring wide = To::Wide(text);
		//for (const auto& ch : wide)
		//	if ((int)ch < 44032 || (int)ch > 55171) return false;

		return true;
	}

}