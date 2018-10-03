//
// Created by Semeyon Svetliy on 03/10/2018.
//

#include "HttpRequest.hpp"
#include "CurrencyConverterApi.hpp"

const string CurrencyConverterApi::getRates(string * args) {
    string url = CurrencyConverterApi::convert_url + (*args).substr(1);
    return HttpRequest::get(&url);
}

const string CurrencyConverterApi::getContries(string *args) {
    string url = CurrencyConverterApi::countries_url + (*args).substr(1);
    return HttpRequest::get(&url);
}

const string CurrencyConverterApi::convert_url = "https://free.currencyconverterapi.com/api/v6/convert?compact=ultra&q=";

const string CurrencyConverterApi::countries_url = "https://free.currencyconverterapi.com/api/v6/countries";