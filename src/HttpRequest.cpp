//
// Created by Semeyon Svetliy on 20.09.2018.
//

#include "restclient-cpp/connection.h"
#include "restclient-cpp/restclient.h"
#include "HttpRequest.hpp"
using namespace std;

string HttpRequest::get(string * url) {
    RestClient::Response r = RestClient::get(* url);
    return r.body;
}
