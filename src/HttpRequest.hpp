//
// Created by Semeyon Svetliy on 21.09.2018.
//

#ifndef GETRATEBOT_HTTPREQUEST_HPP
#define GETRATEBOT_HTTPREQUEST_HPP

#include <string>

using namespace std;

class HttpRequest {

    public:
        static string get(string * url);
};

#endif //GETRATEBOT_HTTPREQUEST_HPP
