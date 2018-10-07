//
// Created by Semeyon Svetliy on 03/10/2018.
//

#ifndef GETRATEBOT_COUNTRIES_HPP
#define GETRATEBOT_COUNTRIES_HPP

#include <string>
#include <fmt/format.h>
using namespace std;

//{"alpha3":"AFG","currencyId":"AFN","currencyName":"Afghan afghani","currencySymbol":"؋","id":"AF","name":"Afghanistan"}
//

struct Country {
    const string alpha3;
    const string currencyId;
    const string currencyName;
    const string currencySymbol;
    const string name;
    const string id;

public:
    string msg() {
        return fmt::format("{0}({1}) – {2}, {3}", this->currencyId, this->currencySymbol, this->currencyName, this->name);
    }

    string forSearch() {
        string msg = fmt::format("{0} {1} {2} {3}", this->currencyId, this->currencyName, this->name, this->currencySymbol);
        return msg;
    }

};


#endif //GETRATEBOT_COUNTRIES_HPP
