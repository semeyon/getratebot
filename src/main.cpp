#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>

#include <tgbot/tgbot.h>
#include "vendors/Logger.hpp"
#include "CurrencyRatesService.hpp"

using namespace std;
using namespace TgBot;

int main() {

    string token(getenv("TOKEN"));
    Logger::info("Token: " + token);

    CurrencyRatesService crService;

    Bot bot(token);
    bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onCommand("help", [&bot](Message::Ptr message) {
        const string info = "rates - returns rate for curency pair, usage example: /rate usd/rub, rub:eur\n"
                            "list - returns list of available curencies, and spam a channel. ";
        bot.getApi().sendMessage(message->chat->id, info);
    });
    bot.getEvents().onCommand("rate", [&bot, &crService](Message::Ptr message) {
        Logger::info("Rate: " + message->text);
        const string content = crService.getMessage(&message->text);
        bot.getApi().sendMessage(message->chat->id, content);
    });
    bot.getEvents().onCommand("list", [&bot, &crService](Message::Ptr message) {
        Logger::info("List: " + message->text);
        vector<string> messages = crService.getContriesMessages();
        for(string content: messages){
            bot.getApi().sendMessage(message->chat->id, content);
        }
    });
    bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
//        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });

    signal(SIGINT, [](int s) {
        Logger::info("SIGINT got " + to_string(s));
        exit(0);
    });

    Logger::info("Bot username: " + bot.getApi().getMe()->username);
    bot.getApi().deleteWebhook();

    TgLongPoll longPoll(bot);
    while (true) {
        try {
            Logger::info("Long poll started");
            longPoll.start();
        } catch (exception& e) {
            Logger::info("Error: " + string(e.what()));
        }
    }

    return 0;
}