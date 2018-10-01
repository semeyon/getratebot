#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>

#include <tgbot/tgbot.h>
#include "vendors/Log.hpp"
#include "CurrencyRatesService.hpp"

using namespace std;
using namespace TgBot;
using namespace njoy;


int main() {

    string token(getenv("TOKEN"));
    Log::info("Token: " + token);

    CurrencyRatesService crService;

    Bot bot(token);
    bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onCommand("help", [&bot](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "/rate USD_RUB,EUR_RUB");
    });
    bot.getEvents().onCommand("rate", [&bot, &crService](Message::Ptr message) {
        Log::info("User wrote " + message->text);
        string content = crService.getMessage(&message->text);
        bot.getApi().sendMessage(message->chat->id, content);
    });
    bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });

    signal(SIGINT, [](int s) {
        Log::info("SIGINT got " + to_string(s));
        exit(0);
    });

    try {
        Log::info("Bot username: " + bot.getApi().getMe()->username);
        bot.getApi().deleteWebhook();

        TgLongPoll longPoll(bot);
        while (true) {
            Log::info("Long poll started");
            longPoll.start();
        }
    } catch (exception& e) {
        Log::info("error: " + string(e.what()));
    }

    return 0;
}