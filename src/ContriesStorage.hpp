//
// Created by Semeyon Svetliy on 07/10/2018.
//

#ifndef GETRATEBOT_CONTRIESSTORAGE_HPP
#define GETRATEBOT_CONTRIESSTORAGE_HPP

#include <string>
#include <vector>
#include "types/Country.hpp"

using namespace std;

class ContriesStorage {
private:
    static ContriesStorage* instance;
    ContriesStorage();
    void fetchData();

public:
    static ContriesStorage* getInstance();
    vector<Country> getAll();
};


#endif //GETRATEBOT_CONTRIESSTORAGE_HPP
