//
// Created by Semeyon Svetliy on 07/10/2018.
//

#include "ContriesStorage.hpp"

ContriesStorage* ContriesStorage::instance = 0;

ContriesStorage* ContriesStorage::getInstance()
{
    if (instance == 0)
    {
        instance = new ContriesStorage();
    }

    return instance;
}

ContriesStorage::ContriesStorage() {}