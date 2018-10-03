//
// Created by Semeyon Svetliy on 03/10/2018.
//

#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

#include "Logger.hpp"
#include "Log.hpp"

using namespace njoy;
using namespace std;

const string Logger::getPrefix() {
    auto now = chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&in_time_t), "[%Y-%m-%d %X] ");
    return ss.str();
}

void Logger::info(string msg) {
    string prefix = Logger::getPrefix();
    Log::info(prefix + msg);
}