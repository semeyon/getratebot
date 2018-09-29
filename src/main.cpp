#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>

#include "vendors/Log.hpp"
#include <tgbot/tgbot.h>
#include "HttpRequest.hpp"

using namespace std;
using namespace TgBot;
using namespace njoy;


int main() {

    string token(getenv("TOKEN"));
    Log::info("Token: %s\n", token.c_str());

    Bot bot(token);
    bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onCommand("help", [&bot](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "/rate USD_RUB,EUR_RUB");
    });
    bot.getEvents().onCommand("rate", [&bot](Message::Ptr message) {
        string url = "https://free.currencyconverterapi.com/api/v6/convert?q=USD_RUB,EUR_RUB";
        string content = HttpRequest::get(&url);
        bot.getApi().sendMessage(message->chat->id, content);
    });
    bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {
        Log::info("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });

    signal(SIGINT, [](int s) {
        Log::info("SIGINT got\n");
        exit(0);
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        bot.getApi().deleteWebhook();

        TgLongPoll longPoll(bot);
        while (true) {
            Log::info("Long poll started\n");
            longPoll.start();
        }
    } catch (exception& e) {
        Log::info("error: %s\n", e.what());
    }

    return 0;
}