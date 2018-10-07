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
#include "types/Country.hpp"

#define MAX_OUT_SIZE 10
#define BITAP_DISTANCE 0
#define MAX_SEARCH_LENGTH 2


using namespace std;

string CurrencyRatesService::parseInputArgs(const string * args) {
    vector<string> _args = split( args->length() > 6 ? (*args).substr(6) : *args, ',');
    auto trimAll = [] (string s) { return trim(s); };
    _args = lambda::map(_args, trimAll);
    auto replAll = [] (string s) { return reduce( s, "_", ":"); };
    _args = lambda::map(_args, replAll);
    auto replSlashes = [] (string s) { return reduce( s, "_", "/"); };
    _args = lambda::map(_args, replSlashes);
    string joinedArgs;
    for (const auto &piece : _args) joinedArgs += ","+piece;
    return joinedArgs.length() > 1 ? joinedArgs.substr(1) : joinedArgs;
}

tuple<int, vector<Rate>, string> CurrencyRatesService::parseRatesResponse(const string * content) {
    int status = 0;
    string error_msg;
    vector<Rate> rates;
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(content->c_str(), root );
    if ( !parsingSuccessful ) {
        Logger::info("Failed to parse: " + reader.getFormattedErrorMessages());
        status = 1;
        error_msg = "There are not such currency or services is not responding, try later";
    } else {
        if ( root.isMember("error") ) {
            status = 2;
            error_msg = root.get("error", "").asString();
        } else {
            string out;
            for (Json::Value::const_iterator it=root.begin(); it!=root.end(); ++it) {
                Rate rate = {
                        it.key().asString().substr(0, 3),
                        it.key().asString().substr(4),
                        it->asFloat()
                };
                rates.push_back(rate);
            }
            if (rates.size() == 0){
                status = 3;
                error_msg = "There are no currency pair";
            }
        }
    }
    tuple<int, vector<Rate>, string> response(status, rates, error_msg);
    return response;
}

string CurrencyRatesService::getMessage(const string * args) {
    const auto joinedArgs = this->parseInputArgs(args);
    const string content = CurrencyConverterApi::getRates(&joinedArgs);
    const tuple<int, vector<Rate>, string> response = this->parseRatesResponse(&content);
    const int status = get<0>(response);
    const vector<Rate> rates = get<1>(response);
    const string errmsg = get<2>(response);
    if (status > 0 ) {
        return errmsg;
    } else {
        string out;
        for(Rate rate : rates) {
            out += "\n"  + rate.msg();
        }
        return out.substr(1);
    }
}

tuple<int, vector<Country>, string> CurrencyRatesService::parseContriesResponse(const string *content){
    int status = 0;
    string error_msg;
    vector<Country> countries;
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(content->c_str(), root );
    if ( !parsingSuccessful ) {
        Logger::info("Failed to parse: " + reader.getFormattedErrorMessages());
        status = 1;
        error_msg = "There are not such currency or services is not responding, try later";
    } else {
        if ( root.isMember("error") ) {
            status = 2;
            error_msg = root.get("error", "").asString();
        } else {
            const Json::Value& results = root["results"];
            string out;
            for (Json::Value::const_iterator it=results.begin(); it!=results.end(); ++it) {
                const string key = it.key().asString();
                const Json::Value& _c = results[key];
                const Country country = {
                        _c["alpha3"].asString(),
                        _c["currencyId"].asString(),
                        _c["currencyName"].asString(),
                        _c["currencySymbol"].asString(),
                        _c["name"].asString(),
                        _c["id"].asString(),
                };
                countries.push_back(country);
            }
            if (countries.size() == 0){
                status = 3;
                error_msg = "There are no currency pair";
            }
        }
    }
    tuple<int, vector<Country>, string> response(status, countries, error_msg);
    return response;
}


vector<string> CurrencyRatesService::getContriesMessages() {
    const string content = CurrencyConverterApi::getContries();
    const tuple<int, vector<Country>, string> response = this->parseContriesResponse(&content);
    const int status = get<0>(response);
    const vector<Country> countries = get<1>(response);
    const string errmsg = get<2>(response);
    vector<string> out;
    if (status > 0 ) {
        out.push_back(errmsg);
    } else {
        for(Country country : countries) {
            out.push_back(country.msg());
        }
    }
    return out;
}

string CurrencyRatesService::parseInputSearchArgs(const string *arg) {
    string _arg = (*arg).substr(7);
    transform(_arg.begin(), _arg.end(), _arg.begin(), ::tolower); //TODO: Move to separate function.
    return trim(_arg);
}

vector<string> CurrencyRatesService::getSearchMessages(const string * args)  {
    vector<string> out;
    map<u_int , string> results;
    const string arg = this->parseInputSearchArgs(args);
    if ( arg.length() > MAX_SEARCH_LENGTH ) {
        const string content = CurrencyConverterApi::getContries();
        const tuple<int, vector<Country>, string> response = this->parseContriesResponse(&content);
        const int status = get<0>(response);
        const vector<Country> countries = get<1>(response);
        const string errmsg = get<2>(response);
        if (status > 0) {
            out.push_back(errmsg);
        } else {
            for (Country country : countries) {
                string msg = country.forSearch();
                transform(msg.begin(), msg.end(), msg.begin(), ::tolower);
                const int position = FuzzyBitapSearch(msg, arg, BITAP_DISTANCE);
                if(position > -1) {
                    results.insert(make_pair(position, country.msg()));
                }
            }
            u_int i = 0;
            for(auto r: results) {
                i++;
                if (i <= MAX_OUT_SIZE) {
                    out.push_back(r.second);
                } else {
                    out.push_back("...");
                    out.push_back("Request returns to many results, make it more specific.");
                    break;
                }
            }

        }
    } else {
        out.push_back("The search request must be at least 3 chars long.");
    }
    return out;
}