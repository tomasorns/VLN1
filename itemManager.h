#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H
#include <iostream>
#include <fstream>

#include "Item.h"

class itemManager
{
public:
    void addItem(Item item);

    void removeItem(Item item);

    bool itemExists(Item item);

    Item getItemByName(string name);

private:


};

#endif // ITEMMANAGER_H
