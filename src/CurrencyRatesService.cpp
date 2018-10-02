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

    vector<string> _args = split((*args).substr(6), ',');

    auto lambda_echo = [](string s ) { Log::info(s); };
    auto trimAll = [] (string s) { return trim(s); };
    _args = lambda::map(_args, trimAll);

    lambda::for_each(_args, lambda_echo);

    auto replAll = [] (string s) { return reduce( s, "_", ":"); };
    _args = lambda::map(_args, replAll);

    Log::info("lambda");
    lambda::for_each(_args, lambda_echo);

    string joinedArgs;
    for (const auto &piece : _args) joinedArgs += ","+piece;


    Log::info("joinedArgs: "+joinedArgs);
    string url = "https://free.currencyconverterapi.com/api/v6/convert?compact=ultra&q="+joinedArgs.substr(1);
    string content = HttpRequest::get(&url);
    Log::info(content);
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(content.c_str(), root );
    Log::info(args->c_str());
    if ( !parsingSuccessful ) {
        Log::info("Failed to parse: " + reader.getFormattedErrorMessages());
        return "There are not such currency or services is not responding, try later";
    } else {
        return fmt::format("USDRUB: {0} \nEURRUB: {1}", root.get("USD_RUB", 0.0).asFloat(), root.get("EUR_RUB", 0.0).asFloat());
    }
}
