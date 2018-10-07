//
// Created by Semeyon Svetliy on 07/10/2018.
//

#include <string>
#include <fmt/format.h>
#include "Country.hpp"

using namespace std;

string Country::msg() {
    return fmt::format("{0}({1}) – {2}, {3}", this->currencyId, this->currencySymbol, this->currencyName, this->name);
}

string Country::forSearch() {
    string msg = fmt::format("{0} {1} {2} {3}", this->currencyId, this->currencyName, this->name, this->currencySymbol);
    return msg;
}

