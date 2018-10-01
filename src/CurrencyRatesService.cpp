//
// Created by Semeyon Svetliy on 01/10/2018.
//

#include <string>
#include "HttpRequest.hpp"
#include "CurrencyRatesService.hpp"

using namespace std;

string CurrencyRatesService::getMessage(string * args) {
    string url = "https://free.currencyconverterapi.com/api/v6/convert?compact=ultra&q=USD_RUB,EUR_RUB";
    string content = HttpRequest::get(&url);
    return content;
}
