//
// Created by Semeyon Svetliy on 29/09/2018.
//

#ifndef GETRATEBOT_CURRENCYCONVERTERAPI_HPP
#define GETRATEBOT_CURRENCYCONVERTERAPI_HPP

#include "<string>"
#include "<vector>"
#include "Rate.hpp"

class CurrencyConverterApi {

    public:
        vector<Rate> getRates(string * rates)

    private:
        const string baseUrl = "https://free.currencyconverterapi.com/api/v6/convert?q=";

};


#endif //GETRATEBOT_CURRENCYCONVERTERAPI_HPP
