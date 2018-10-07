//
// Created by Semeyon Svetliy on 01/10/2018.
//

#ifndef GETRATEBOT_CURRENCYRATESSERVICE_HPP
#define GETRATEBOT_CURRENCYRATESSERVICE_HPP

#include <string>
#include "types/Rate.hpp"
#include "types/Country.hpp"

using namespace std;

class CurrencyRatesService {

public:
    string getMessage(const string * args);
    vector<string> getContriesMessages();
    vector<string> getSearchMessages(const string * args);

private:
    string parseInputArgs(const string * args);
    string parseInputSearchArgs(const string * arg);
    tuple<int, vector<Rate>, string> parseRatesResponse(const string * content);
    tuple<int, vector<Country>, string> parseContriesResponse(const string * content);

};


#endif //GETRATEBOT_CURRENCYRATESSERVICE_HPP
