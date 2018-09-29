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
    Log::info("Token: " + token);

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
        Log::info("User wrote " + message->text);
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