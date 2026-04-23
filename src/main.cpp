#include <dpp/dpp.h>
#include <iostream>
#include <string>
#include <fstream>

std::string load_DT(const std::string& filename) {
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "couldnt open file" << filename << std::endl;
		return"";
	}

	std::string line;

	while (std::getline(file, line)) {
		if (line.rfind("DISCORD_TOKEN=", 0) == 0) {
			std::string token = line.substr(14);

			token.erase(token.find_last_not_of("\r\n\t") + 1);

			return token;
		}
	}

	return "";

}

int main()
{

	std::string BOT_TOKEN = load_DT("Tokers.yap");

	if (BOT_TOKEN.empty()) {
		std::cerr << "Failed to load the bot token\n";
		return 1;
	}

	dpp::cluster bot(BOT_TOKEN);

	bot.on_log(dpp::utility::cout_logger());

	bot.on_ready([&bot](const dpp::ready_t& event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			std::vector<dpp::slashcommand> commands {
				{ "ping", "Ping pong!", bot.me.id }
			};

			bot.global_bulk_command_create(commands);
		}
	});

	bot.on_slashcommand([](const dpp::slashcommand_t& event) -> dpp::task<void> {
		if (event.command.get_command_name() == "ping") {
			co_await event.co_reply("Pong!");
		}
		co_return;
	});

	bot.start(dpp::st_wait);

	return 0;
}