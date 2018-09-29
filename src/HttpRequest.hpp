//
// Created by Semeyon Svetliy on 21.09.2018.
//

#ifndef FEEDBRIDGE_HTTPCLIENT_H
#define FEEDBRIDGE_HTTPCLIENT_H

#include <string>

using namespace std;
class HttpRequest {

    public:
        static string get(string * url);
};

#endif //FEEDBRIDGE_HTTPCLIENT_H
