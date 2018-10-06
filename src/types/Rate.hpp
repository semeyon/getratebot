//
// Created by Semeyon Svetliy on 29/09/2018.
//

#ifndef GETRATEBOT_RATE_HPP
#define GETRATEBOT_RATE_HPP

#include <string>
#include <fmt/format.h>

struct Rate {
    const string from;
    const string to;
    const float val;

public:
    string msg() {
        return fmt::format("1 {0} = {1} {2}", this->from, this->val, this->to);
    }
};
#endif //GETRATEBOT_RATE_HPP
