//
// Created by Semeyon Svetliy on 01/10/2018.
//

#include <string>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <fmt/format.h>

#include "vendors/Log.hpp"
#include "vendors/Strings.hpp"
#include "vendors/Lambda.cpp"
#include "HttpRequest.hpp"
#include "CurrencyRatesService.hpp"
#include "Rate.hpp"


using namespace std;
using namespace njoy;

string CurrencyRatesService::getMessage(string * args) {

    // Parse args
    Log::info("getMessage");
    Log::info(*args);
    Log::info((*args).substr(6));
    vector<string> _args = split( args->length() > 6 ? (*args).substr(6) : *args, ',');

//    Log::info(_args);
    auto lambda_echo = [](string s ) { Log::info(s); };
    auto trimAll = [] (string s) { return trim(s); };
    _args = lambda::map(_args, trimAll);

    lambda::for_each(_args, lambda_echo);

    auto replAll = [] (string s) { return reduce( s, "_", ":"); };
    _args = lambda::map(_args, replAll);

    auto replSlashes = [] (string s) { return reduce( s, "_", "/"); };
    _args = lambda::map(_args, replSlashes);

    Log::info("lambda");
    lambda::for_each(_args, lambda_echo);

    string joinedArgs;
    for (const auto &piece : _args) joinedArgs += ","+piece;
//    Log::info("joinedArgs: "+joinedArgs);

    //Request!
    string url = "https://free.currencyconverterapi.com/api/v6/convert?compact=ultra&q="+joinedArgs.substr(1);
    string content = HttpRequest::get(&url);

    // parse request
    Log::info("content");
    Log::info(content);
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(content.c_str(), root );

    // Create message
    Log::info(args->c_str());
    if ( !parsingSuccessful ) {
        Log::info("Failed to parse: " + reader.getFormattedErrorMessages());
        return "There are not such currency or services is not responding, try later";
    } else {
        if ( root.isMember("error") ) {
            return root.get("error", "").asString();
        } else {
            string out;
            for (Json::Value::const_iterator it=root.begin(); it!=root.end(); ++it) {
                Log::info(it.key().asString());
                Log::info(it->asFloat());
                out += "\n" + fmt::format("1 {0} = {1} {2}", it.key().asString().substr(0, 3), it->asFloat(), it.key().asString().substr(4));
            }
            return out.length() > 0 ? out.substr(1) : "There are no currency pair";
        }

//        return fmt::format("USDRUB: {0} \nEURRUB: {1}", root.get("USD_RUB", 0.0).asFloat(), root.get("EUR_RUB", 0.0).asFloat());
    }
}
