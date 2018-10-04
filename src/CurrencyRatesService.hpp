//
// Created by Semeyon Svetliy on 01/10/2018.
//

#ifndef GETRATEBOT_CURRENCYRATESSERVICE_HPP
#define GETRATEBOT_CURRENCYRATESSERVICE_HPP

#include <string>

using namespace std;

class CurrencyRatesService {

public:
    string getMessage(string * args);
    string getContries();

private:
    void parseInputArgs(string * args);
    void parseRatesResponse(string content);
    void parseContriesResponse(string content);

};


#endif //GETRATEBOT_CURRENCYRATESSERVICE_HPP
