//
// Created by Semeyon Svetliy on 03/10/2018.
//

#ifndef GETRATEBOT_COUNTRIES_HPP
#define GETRATEBOT_COUNTRIES_HPP

#include <string>
#include <fmt/format.h>
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
        return fmt::format("{0}({1}) – {2}, {3}", this->alpha3, this->currencySymbol, this->currencyName, this->name);
    }

};


#endif //GETRATEBOT_COUNTRIES_HPP
