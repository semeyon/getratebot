//
// Created by Semeyon Svetliy on 03/10/2018.
//

#ifndef GETRATEBOT_LOGGER_HPP
#define GETRATEBOT_LOGGER_HPP

#include <string>

using namespace std;

class Logger {

public:
    static void info(string msg);

private:
    static const string getPrefix();

};


#endif //GETRATEBOT_LOGGER_HPP
