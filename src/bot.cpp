#include <dpp/dpp.h>
#include <iostream>
#include "token.h"
#include "llamatalk.hpp"
#include <unordered_map>

const std::string BOT_TOKEN = stored_BOT_TOKEN;

int main() {
    dpp::cluster bot(BOT_TOKEN);
    LLamaTalk chatbot = LLamaTalk("127.0.0.1",11434);
    
    bot.on_ready([&bot, &chatbot](const dpp::ready_t& event) {
        std::cout << "Bot ready" << std::endl;
        if (dpp::run_once<struct register_bot_commands>()){
            bot.global_command_create(dpp::slashcommand("ping","ping the bot now", bot.me.id));
            bot.global_command_create(dpp::slashcommand("list","Get a list of all the available chat models", bot.me.id));
            // bot.global_command_create(dpp::slashcommand("chat","Give a bot an input", bot.me.id));
            dpp::slashcommand chat("chat","Give a bot an input", bot.me.id);
            dpp::command_option modelchoice(dpp::co_string, "model", "Choose model to talk with", true);
            for (auto key:chatbot.get_models()) {
                modelchoice.add_choice(dpp::command_option_choice(key.first, std::string(key.first)));
            }
            chat.add_option(
                modelchoice
            );
            dpp::command_option prompt(dpp::co_string, "prompt", "Prompt for the bot", true);
            chat.add_option(
                prompt
            );
            bot.global_command_create(chat);
        }
    });

    bot.on_slashcommand([&bot, &chatbot](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            bot.message_create(dpp::message(event.command.channel_id, "Testing outptut"));
            event.reply("Pong!");
        } else if (event.command.get_command_name() == "list") {
            event.thinking(false, [&chatbot, event](const dpp::confirmation_callback_t& callback) {
                std::unordered_map<std::string, std::string> modelmap = chatbot.get_models();
                std::string output = "# Name : Model\n";
                for (auto key:modelmap) {
                    output+="- **"+key.first+"** : "+key.second+"\n";
                }
                event.edit_original_response(dpp::message(output));
            });
        } else if (event.command.get_command_name() == "chat") {
            event.thinking(false, [&chatbot, &bot, event](const dpp::confirmation_callback_t& callback) {
                std::string model = std::get<std::string>(event.get_parameter("model"));
                std::string prompt = std::get<std::string>(event.get_parameter("prompt"));\
                std::string output = chatbot.chat(model,prompt), str;
                std::stringstream outstream(output);
                event.edit_original_response(dpp::message("output"));
                if (output.size() > 2000) {
                    for (int i = 0; i<= output.size()/2000; i++) {
                        bot.message_create(dpp::message(event.command.channel_id, output.substr(i*2000, 2000)));
                    }
                } else if (output.size() <= 2000) {
                    bot.message_create(dpp::message(event.command.channel_id, output));
                }
            });
        }
    });
    bot.start(dpp::st_wait);
}