//
// Created by Semeyon Svetliy on 03/10/2018.
//

#ifndef GETRATEBOT_CURRENCYCONVERTERAPI_HPP
#define GETRATEBOT_CURRENCYCONVERTERAPI_HPP

#include <string>

using namespace std;

class CurrencyConverterApi {

public:
    static const string getRates(string * args);
    static const string getContries(string * args);

private:
    static const string convert_url;
    static const string countries_url;


};


#endif //GETRATEBOT_CURRENCYCONVERTERAPI_HPP
