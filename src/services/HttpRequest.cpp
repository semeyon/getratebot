//
// Created by Semeyon Svetliy on 20.09.2018.
//

#include "restclient-cpp/connection.h"
#include "restclient-cpp/restclient.h"
#include "../vendors/Logger.hpp"
#include "HttpRequest.hpp"

using namespace std;
using namespace njoy;

string HttpRequest::get(string * url) {
    Logger::info("Request for " + *url);
    RestClient::Response r = RestClient::get(* url);
    return r.body;
}
