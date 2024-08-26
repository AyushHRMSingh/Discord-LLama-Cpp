#include <dpp/dpp.h>
#include <iostream>
#include "include/token.h"

const std::string BOT_TOKEN = stored_BOT_TOKEN;

int main() {
    dpp::cluster bot(BOT_TOKEN);

    bot.on_ready([&bot](const dpp::ready_t& event) {
        std::cout << "Bot ready" << std::endl;
        if (dpp::run_once<struct register_bot_commands>()){
            bot.global_command_create(dpp::slashcommand("ping","ping the bot now", bot.me.id));
        }
    });

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        std::cout<<"bot command executed"<<std::endl;
        std::cout<<event.command.get_command_name()<<std::endl;
        event.reply("testing 123");
    });

    bot.start(dpp::st_wait);
}