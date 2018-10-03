//
// Created by Semeyon Svetliy on 01/10/2018.
//

#include <string>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <fmt/format.h>

#include "vendors/Logger.hpp"
#include "vendors/Strings.hpp"
#include "vendors/Lambda.cpp"
#include "services/CurrencyConverterApi.hpp"
#include "CurrencyRatesService.hpp"
#include "types/Rate.hpp"


using namespace std;

string CurrencyRatesService::getMessage(string * args) {

    // Parse args
    vector<string> _args = split( args->length() > 6 ? (*args).substr(6) : *args, ',');

//    Logger::info(_args);
    auto lambda_echo = [](string s ) { Logger::info(s); };
    auto trimAll = [] (string s) { return trim(s); };
    _args = lambda::map(_args, trimAll);

    lambda::for_each(_args, lambda_echo);

    auto replAll = [] (string s) { return reduce( s, "_", ":"); };
    _args = lambda::map(_args, replAll);

    auto replSlashes = [] (string s) { return reduce( s, "_", "/"); };
    _args = lambda::map(_args, replSlashes);

    lambda::for_each(_args, lambda_echo);

    string joinedArgs;
    for (const auto &piece : _args) joinedArgs += ","+piece;
//    Logger::info("joinedArgs: "+joinedArgs);

    //Request!
    string content = CurrencyConverterApi::getRates(&joinedArgs);

    // parse request
//    Logger::info("content");
//    Logger::info(content);
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(content.c_str(), root );

    // Create message
//    Logger::info(args->c_str());
    if ( !parsingSuccessful ) {
        Logger::info("Failed to parse: " + reader.getFormattedErrorMessages());
        return "There are not such currency or services is not responding, try later";
    } else {
        if ( root.isMember("error") ) {
            return root.get("error", "").asString();
        } else {
            string out;
            for (Json::Value::const_iterator it=root.begin(); it!=root.end(); ++it) {
//                Logger::info(it.key().asString());
//                Logger::info(it->asFloat());
                out += "\n" + fmt::format("1 {0} = {1} {2}", it.key().asString().substr(0, 3), it->asFloat(), it.key().asString().substr(4));
            }
            return out.length() > 0 ? out.substr(1) : "There are no currency pair";
        }

    }
}

string CurrencyRatesService::getContries() {
    string content = CurrencyConverterApi::getContries();
    return content.substr(0, 4000);
}
