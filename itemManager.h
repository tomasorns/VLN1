#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <list>

#include "Item.h"

class itemManager
{
public:
    void addItem(Item item);

    void removeItem(list<Item> item);

    bool itemExists(string name);

    list<Item> searchItem(string name);

    Item reconstructItem(string line);

    void getAllItemsListed(string command);

    void getNextValId();

    void setId(int newId){id = newId;}

    int getId(){return id;}

    void printList(list<Item> item);

private:
    int id; //TODO: add get & set for identifier

    bool is_empty();

};

#endif // ITEMMANAGER_H
